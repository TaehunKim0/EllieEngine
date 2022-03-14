
struct VS_INPUT
{
	float4 position : POSITION;
    float2 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 color : COLOR;
};

cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;
    
    Input.position.w = 1;
    
    Output.position = mul(Input.position, worldMatrix);
    Output.position = mul(Input.position, viewMatrix);
    Output.position = mul(Input.position, projectionMatrix);
	
    Output.color = Input.color;
    
	return Output;
}