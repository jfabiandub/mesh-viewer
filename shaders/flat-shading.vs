#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;


flat out vec3 LightIntensity;
struct LightInfo {
vec4 pos; // Light position in eye coords.
vec3 La;    // Ambient light 
vec3 Ld;    // Diffuse light 
vec3 Ls;    // Specular light 
};

uniform LightInfo Light;

struct MaterialInfo {
vec3 Ka;            // Ambient reflectivity
vec3 Kd;            // Diffuse reflectivity
vec3 Ks;            //specular reflect
float shine;    // Specular shininess factor
};

uniform MaterialInfo Material;

vec3 phong(vec4 eye_pos, vec3 eye_n){

   //vec3 eye_n = normalize(eye_normal);
   vec3 s = normalize(vec3(Light.pos - eye_pos));
   vec3 v = normalize(vec3(-eye_pos));
   vec3 r = reflect(-s, eye_n); 
   

   vec3 ambient = Light.La * Material.Ka;
   float sDotN = max( dot(s,eye_n), 0.0 );
   vec3 diffuse = Light.Ld * Material.Kd * sDotN;

   vec3 spec = vec3(0.0);

    if (sDotN > 0.0)
      spec= Light.Ls * Material.Ks * pow(max(dot(r, v), 0.0), Material.shine);
   return ambient + diffuse + spec;
    
}
void main()
{

   vec3 eye_n = normalize(NormalMatrix * vNormals);
   vec4 eye_pos = ModelViewMatrix * vec4(vPos, 1.0);
   
   LightIntensity = phong(eye_pos, eye_n);
   gl_Position = MVP * vec4(vPos, 1.0);
}
