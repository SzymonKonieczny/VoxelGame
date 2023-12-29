#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoordsOffset;
uniform mat4 modelMatrix;

out vec2 TexCoordsOffset;

void main()
{
    TexCoordsOffset = aTexCoordsOffset;
    vec4 tempPos = modelMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0); 
    gl_Position = (tempPos - vec4(0.5f))*2; //transform from -1 -> 1 into 0 -> 1 ranges
}  