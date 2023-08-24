#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aCol;
out vec3 Col;
out vec2 TexCoord;
uniform mat4 viewProjMatrix;
uniform mat4 modelMatrix;

void main()
{
   Col = aCol;
   TexCoord = aTexCoord;
   //gl_Position = vec4(aPos.x, aPos.y , aPos.z, 1.0);
   gl_Position = viewProjMatrix * modelMatrix * vec4(aPos.x,aPos.y,aPos.z,1.0) ;
}