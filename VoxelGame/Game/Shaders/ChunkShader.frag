#version 330 core
out vec4 FragColor;
in vec3 Col;
in vec2 TexCoord;

in vec4  FragPosLightSpace;

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
	float currentDepth = projCoords.z ;//linearizeDepth(projCoords.z,0.1f, 1000.f);  
	float bias = 0.000;
	float shadow = currentDepth -bias> closestDepth  ? 1.0 : 0.5;  
	return shadow;
}
void main()
{	
	vec4 pixel;

	 pixel = texture(tex0 , TexCoord);
	FragColor = vec4( vec4(Col, 1.0f)*pixel* CalculateShadow( FragPosLightSpace));
	

}