
struct VS_INPUT
{
	float4 mPosition : POSITION;
    float2 mtex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition : SV_POSITION;
	float2 mtex : TEXCOORD0;
};

cbuffer MatrixBuffer
{
	matrix gWorldMatrix;
	matrix gViewMatrix;
	matrix gProjectionMatrix;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
	Output.mPosition = mul(Input.mPosition, gViewMatrix);
	Output.mPosition = mul(Input.mPosition, gProjectionMatrix);
    Output.mtex = Input.mtex;
	
	return Output;
}