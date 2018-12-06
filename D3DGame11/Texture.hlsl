// Vertex Shader�� ���� ����
// ���� ��ȯ�� ���ش�.
// ������ �� ������ŭ �������̴��� ����(���⼭�� ������ 6�� ���������Ƿ� 6�� ȣ���Ѵ�)

// cbuffer : constant buffer
// register(���)
// b : buffer
// t : texture
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

// t0 : Texture0��� �ǹ��̴�.
// Diffuse : ���� ������ �ִ� ���� �߻��ϴ� ��(������ ���� ���� �ݻ�� ���� ������ ���� ���̴� �������� ��ǻ�Ϳ��� ���� ���� ������ �ڱ� ���� �߻��Ѵ�.)
Texture2D DiffuseMap : register(t0);
// �� �ؽ��ĸ� �׸��� � ������ ���̰� � ������ ǥ���� �������� �˷��ִ� ��(Rasterize�� ����ϴ�)
SamplerState DiffuseSamp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    return DiffuseMap.Sample(DiffuseSamp, input.UV);
}