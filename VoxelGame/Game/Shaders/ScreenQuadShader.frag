#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D depthTexture;

void main()
{
   //vec3 col = texture(screenTexture, TexCoords).rgb;
   //FragColor = vec4(col, 1.0);
    float depthValue = texture(screenTexture, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0);
} 