#version 330 core

out vec4 FragColor;
in vec3 Col;

void main()
{
   FragColor = vec4(Col, 1.0f);
}