
#version 330 core
float linearizeDepth(float depth, float nearClip, float farClip)
{


    float z = depth* 2.0 - 1.0;;
    return ((2.0 * nearClip * farClip) / (farClip + nearClip - z * (farClip - nearClip)))/farClip;
}
void main()
{             
     float depthNDC = gl_FragCoord.z;
     float farClip = 1000.f;
    float nearClip = 0.1f;
    float linearDepth = linearizeDepth(depthNDC, nearClip, farClip);
    // gl_FragDepth = linearDepth; Doing nothing for now
}  