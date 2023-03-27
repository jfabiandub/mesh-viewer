#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormals;
layout (location = 2) in vec2 vTextureCoords;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform bool HasUV;

out vec3 eye_normal;
out vec4 eye_pos;
out vec2 uv;


void main()
{
  // get the normal and vertex position to eye coordinates
  eye_normal= normalize(NormalMatrix * vNormals);
  eye_pos= ModelViewMatrix * vec4(vPos, 1.0);

  uv= vTextureCoords;
  
  gl_Position = MVP * vec4(vPos, 1.0);
  }