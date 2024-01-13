#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aCol;
out vec3 Col;
out vec2 TexCoord;

out  vec4 FragPosLightSpace;

uniform mat4 viewProjMatrix;
uniform mat4 modelMatrix;
uniform mat4 lightSpaceMatrix;


//uniform vec3 lightPos;
//uniform vec3 viewPos;

void main()
{
   Col = aCol;
   TexCoord = aTexCoord;

   FragPosLightSpace = lightSpaceMatrix * vec4( vec3(modelMatrix* vec4(aPos,1.0)),1.0);

   gl_Position = viewProjMatrix * modelMatrix * vec4(aPos,1.0) ;

}