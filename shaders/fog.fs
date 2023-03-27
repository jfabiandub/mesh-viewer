#version 400

in vec4 eye_pos;
in vec3 eye_normal;

struct LightInfo {
    vec4 pos;
    vec3 intensity;
};

uniform LightInfo Light;

struct FogInfo {
  float maxDist;
  float minDist;
  vec3 color;
};

uniform FogInfo Fog;

struct MaterialInfo {
   vec3 Ka;    // Ambient reflectivity
   vec3 Kd;    // Diffuse reflectivity
   vec3 Ks;    // Specular reflectivity
   float shine;    // Specular shininess factor
};

uniform MaterialInfo Material;

uniform sampler2D diffuseTexture;
uniform bool HasUV; 
in vec2 uv; 
const float uvScale= .0f; 

out vec4 FragColor;

vec3 ads() {
  vec3 eye_n = normalize(eye_normal);
  vec3 s = normalize(vec3(Light.pos - eye_pos));
  vec3 v = normalize(vec3(-eye_pos));
  vec3 r = reflect( -s, eye_n );

  vec3 ambient = Light.intensity * Material.Ka;
  float sDotN = max(dot(s,eye_n), 0.0 );
  vec3 diffuse = Light.intensity * Material.Kd * sDotN;
  vec3 spec = vec3(0.0);

  if (sDotN > 0.0f)
    spec= Light.intensity * Material.Ks * pow(max(dot(r, v), 0.0), Material.shine);

  vec3 color;
  if (HasUV) {
    color= (ambient + diffuse) * texture(diffuseTexture, uv * uvScale).xyz + spec;
  } else {
    color= ambient + diffuse + spec;
  }

  return color;
}

void main() {
  float dist = length(eye_pos); 
  float fogFactor = clamp((Fog.maxDist - dist) / (Fog.maxDist - Fog.minDist), 0.0, 1.0); // calculate the fog factor

  vec3 shadeColor = ads();
  vec3 color = mix(Fog.color, shadeColor, fogFactor);


  float fogDensity = 0.10; 
  float fogAmount = 1.2 - exp(-fogDensity * fogDensity * dist * dist);
  color = mix(color, Fog.color, fogAmount);

  FragColor = vec4(color, 1.0);
}