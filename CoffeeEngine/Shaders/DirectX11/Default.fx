//////////////
// TYPEDEFS //
//////////////
struct SimpleVertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 texIn : TEXCOORD0;
    float3 normal: NORMAL;
};

struct SimplePixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 texIn : TEXCOORD0;
    float3 normal: NORMAL;
};

//////////////////
// Forward Decs //
//////////////////

float4 GammaToLinear(float4 color);
float4 LinearToGamma(float4 color);

/////////////
// GLOBALS //
/////////////

SamplerState SampleType;
Texture2D shaderTexture;

cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
SimplePixelInputType DefaultVertexShader(SimpleVertexInputType input)
{
    SimplePixelInputType output;

    // Set the homogenous component of the vector.
    input.position.w = 1.0f;

    // Transform the position against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    //Copy the color and texture information.
    output.color = input.color;
    output.texIn = input.texIn;
    
	//Transform the vertex's normal against the world matrix and normalize it.
    //output.normal = mul(input.normal, (float3x3)worldMatrix);
    //output.normal = normalize(output.normal);
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 DefaultPixelShader(SimplePixelInputType input) : SV_TARGET
{
    float3 lightDir;
    float lightIntensity;

    float4 textureColor = shaderTexture.Sample(SampleType, input.texIn);
    //lightDir = -lightDirection;

    //lightIntensity = saturate(dot(input.normal, lightDir));
    //color = saturate(diffuseColor * lightIntensity);

	//Get pixels color and blend it with the texture's color.
	return LinearToGamma(textureColor) * input.color;
}

float4 GammaToLinear(float4 color)
{
	//Gamma 2.2 (1/2.2f)
	return pow(color, 2.2f);
}

float4 LinearToGamma(float4 color)
{
	//Gamma 2.2 (1/2.2f)
	return pow(color, 0.4545f);
}