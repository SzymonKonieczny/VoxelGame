#version 330 core
out vec4 FragColor;
in vec3 Col;
in vec2 TexCoord;
uniform sampler2D tex0;

void main()
{
	vec4 pixel = texture(tex0 , TexCoord);
//	if(pixel.w < 0.1) discard;
	FragColor = vec4( vec4(Col, 1.0f)*pixel );

	//FragColor = vec4((color, 1.0f)*  pixel);




	

}