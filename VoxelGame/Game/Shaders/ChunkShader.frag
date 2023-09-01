#version 330 core
out vec4 FragColor;
in vec3 Col;
in vec2 TexCoord;
uniform sampler2D tex0;
uniform sampler2D shadowDepthTexture;

void main()
{	
	vec4 pixel1;
	vec4 pixel2;
	vec4 pixel;

	 pixel1 = texture(tex0 , TexCoord);
	 pixel2 = texture(shadowDepthTexture , TexCoord);
	 pixel = (pixel1+pixel2)/2;
//	if(pixel.w < 0.1) discard;
	FragColor = vec4( vec4(Col, 1.0f)*pixel );

	//FragColor = vec4((color, 1.0f)*  pixel);




	

}