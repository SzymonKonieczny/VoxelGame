#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
   vec3 col = vec3(1.f,0.f,1.f);//texture(screenTexture, TexCoords).rgb;
   FragColor = vec4(col, 1.0);

} 