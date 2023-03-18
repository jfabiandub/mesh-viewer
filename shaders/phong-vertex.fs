#version 400

in vec3 res;
out vec4 FragColor;

void main()
{
   FragColor = vec4(res, 1.0);
}
