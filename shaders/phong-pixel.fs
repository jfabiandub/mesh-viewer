#version 400

out vec4 FragColor;
in vec3 eye_normal;
in vec4 eye_pos;

struct LightInfo {
   vec4 pos;   //Light position in eye coords.
   vec3 La;    //Ambient light intensity
   vec3 Ld;    //Diffuse light intensity
   vec3 Ls;    // Specular light intensity
};

uniform LightInfo Light;

struct MaterialInfo {
   vec3 Ka;    // Ambient reflectivity
   vec3 Kd;    // Diffuse reflectivity
   vec3 Ks;    // Specular reflectivity
   float shine;    // Specular shininess factor
};

uniform MaterialInfo Material;

vec3 phong(){
   vec3 s;
   vec3 eye_n = normalize(eye_normal);
    if (Light.pos.w == 0.0f) // directional light source
      s= normalize(vec3(Light.pos));
   else // positional light source
      s= normalize(vec3(Light.pos - eye_pos));
    vec3 v = normalize(vec3(-eye_pos));
    vec3 r = reflect( -s, eye_n );

    vec3 ambient = Light.La * Material.Ka;
    float sDotN = max( dot(s,eye_n), 0.0 );
    vec3 diffuse = Light.Ld * Material.Kd * sDotN;
    vec3 spec = vec3(0.0);

    if (sDotN > 0.0f)
      spec= Light.Ls * Material.Ks * pow(max(dot(r, v), 0.0), Material.shine);
   return ambient + diffuse + spec;
    
}


void main()
{
   FragColor = vec4(phong(), 1.0);
}