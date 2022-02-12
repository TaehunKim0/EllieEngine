
struct VS_INPUT
{
	float mPosition : POSITION;
};

struct VS_OUTPUT
{
	float mPosition : POSITION;
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
	
	return Output;
}