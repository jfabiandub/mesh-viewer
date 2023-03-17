#version 400
in vec3 _normal;
out vec4 FragColor;
void main()
{
   FragColor = vec4(_normal.x, _normal.y, _normal.z, 1.0);
}
