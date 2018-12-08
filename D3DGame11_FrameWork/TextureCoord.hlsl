
cbuffer WorldViewProjectionBuffer : register(b0)
{
    //float4x4 = matrix(같은 말이다)

    matrix World;
    matrix View;
    matrix Projection;
};

struct VertexInput
{
	float4 Position : POSITION0;
    // TEXCOORD : Texture의 좌표계라는 의미이다.
	float2 UV : TEXCOORD0;
};

struct PixelInput
{
	// SV => System Value;
	// SV는 무조건 써야하는 값에 사용한다.

    float4 Position : SV_POSITION0;
    float2 UV : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
    // GPU가 계산이 더 빠르다.
    // CPU에서 계산을 다 하고 Shader에 넘겨줘도 되긴하다.

    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.UV = input.UV;

    return output;
}

Texture2D DiffuseMap : register(t0);
Texture2D DiffuseMap2 : register(t1);
SamplerState DiffuseSamp : register(s0);


float4 PS(PixelInput input) : SV_TARGET
{
    float4 color = 0; // 0으로 하면 0이 자동으로 채워진다.

    if(input.UV.x < 1.0f)
        color = DiffuseMap.Sample(DiffuseSamp, input.UV);

    if (input.UV.x > 1.0f)
        color = DiffuseMap2.Sample(DiffuseSamp, float2(input.UV.x - 1.0f, input.UV.y));

    return color;

}