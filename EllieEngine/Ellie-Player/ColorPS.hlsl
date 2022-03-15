struct PixelInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

float4 main(PixelInputType input) : SV_TARGET
{
    return input.color;
}