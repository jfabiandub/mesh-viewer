#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUV;


uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

out vec3 _normal; 

void main()
{  
   vec3 _n = vNormal;
   _normal = vec3((_n.x + 1)/2, (_n.y + 1)/2, (_n.z + 1)/2);

   
   gl_Position = MVP * vec4(vPos, 1.0);
}
