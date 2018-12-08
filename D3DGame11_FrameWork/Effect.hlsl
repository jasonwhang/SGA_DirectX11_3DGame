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
	// HLSL�� �⺻������ float �ڷ����ۿ� ����� �� ���� ����
	float4 Position : POSITION0;
	float4 Color : COLOR0;
};

struct PixelInput
{
	// SV => System Value;
	// SV�� ������ ����ϴ� ���� ����Ѵ�.

    float4 Position : SV_POSITION0;
    float4 Color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    // GPU�� ����� �� ������.
    // CPU���� ����� �� �ϰ� Shader�� �Ѱ��൵ �Ǳ��ϴ�.

    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Color = input.Color;

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return input.Color;
}