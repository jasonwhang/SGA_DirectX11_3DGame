
cbuffer WorldViewProjectionBuffer : register(b0)
{
    //float4x4 = matrix(���� ���̴�)

    matrix World;
    matrix View;
    matrix Projection;
};

struct VertexInput
{
	float4 Position : POSITION0;
    // TEXCOORD : Texture�� ��ǥ���� �ǹ��̴�.
	float2 UV : TEXCOORD0;
};

struct PixelInput
{
	// SV => System Value;
	// SV�� ������ ����ϴ� ���� ����Ѵ�.

    float4 Position : SV_POSITION0;
    float2 UV : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
    // GPU�� ����� �� ������.
    // CPU���� ����� �� �ϰ� Shader�� �Ѱ��൵ �Ǳ��ϴ�.

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
    float4 color = 0; // 0���� �ϸ� 0�� �ڵ����� ä������.

    if(input.UV.x < 1.0f)
        color = DiffuseMap.Sample(DiffuseSamp, input.UV);

    if (input.UV.x > 1.0f)
        color = DiffuseMap2.Sample(DiffuseSamp, float2(input.UV.x - 1.0f, input.UV.y));

    return color;

}