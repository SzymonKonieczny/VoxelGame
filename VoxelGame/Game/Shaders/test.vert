#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
out vec3 Col;
uniform vec2 testUni;
void main()
{
   Col = aCol;
   gl_Position = vec4(aPos.x + testUni.x, aPos.y + testUni.y, aPos.z, 1.0);
}