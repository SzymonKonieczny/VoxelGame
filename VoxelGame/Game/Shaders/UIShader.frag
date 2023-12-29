#version 330 core
out vec4 FragColor;

in vec2 TexCoordsOffset;
uniform vec2 TexCoords;


uniform sampler2D itemAtlas;

void main()
{
   vec4 col = texture(itemAtlas, TexCoords + TexCoordsOffset).rgbw;
	 if(col.w == 0) discard;


   FragColor = col;

} 