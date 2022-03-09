
Texture2D shaderTexture;
SamplerState SampleType;

struct PixelInputType
{
    float4 position : SV_Position;
    float2 tex : TEXCOORD0;
};

float4 main(PixelInputType input) : SV_Target
{
    float4 textureColor;
    textureColor = shaderTexture.Sample(SampleType, input.tex);
    
    return textureColor;
}