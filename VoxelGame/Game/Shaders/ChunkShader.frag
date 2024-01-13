#version 330 core
out vec4 FragColor;
in float FaceBaseLight;

in float BlockLightLevel;
in vec2 TexCoord;

in vec4  FragPosLightSpace;


//uniform int flatSunlightLevel;
uniform sampler2D tex0;
uniform sampler2D shadowDepthTexture;
float linearizeDepth(float depth, float nearClip, float farClip)
{


    float z = depth* 2.0 - 1.0;;
    return ((2.0 * nearClip * farClip) / (farClip + nearClip - z * (farClip - nearClip)))/farClip;
}
float CalculateShadow(vec4 fragPosLightSpace)
{
   // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5; 
	float closestDepth = texture(shadowDepthTexture, projCoords.xy).r;   
	float currentDepth = projCoords.z ;	 
	float bias = 0.005;
	float shadow = currentDepth -bias< closestDepth  ? 0.5 : 0.0;  
	return shadow;
}
void main()
{	
	vec4 pixel;

	 pixel = texture(tex0 , TexCoord);
	 if(pixel.w == 0) discard;
	 //FragColor = vec4( vec4(Col, 1.0f)*pixel);

	float Sunlight = 0.6; // to be changed into a uniform
	vec3 AddedLight; //from blockLightLevel (torches/flowers) and the sun

	if (CalculateShadow( FragPosLightSpace) > 0.f) 
		AddedLight =    vec3(max(BlockLightLevel, Sunlight)); 
	else 
		AddedLight = vec3(BlockLightLevel);

	

	vec3 light ;
	light = vec3(FaceBaseLight) + AddedLight;
	FragColor = vec4( vec4(light, 1.0f)*pixel);
	//FragColor = vec4( vec4(BlockLightLevel + FaceBaseLight, 1.0f)*pixel);





	//FragColor = vec4( vec4(Col, 1.0f)*pixel*  (1-CalculateShadow( FragPosLightSpace)));
	

}