#version 330 core
out vec4 FragColor;

uniform vec2 TexCoords;

uniform sampler2D itemAtlas;

void main()
{
   vec3 col = vec3(TexCoords.x);//texture(screenTexture, TexCoords).rgb;
   FragColor = vec4(col, 1.0);

} 