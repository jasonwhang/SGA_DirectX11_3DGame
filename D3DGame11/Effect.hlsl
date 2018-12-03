// Vertex Shader�� ���� ����
// ���� ��ȯ�� ���ش�.
// ������ �� ������ŭ �������̴��� ����(���⼭�� ������ 6�� ���������Ƿ� 6�� ȣ���Ѵ�)

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

// ������ �� ����� �´�.
//PixelInput VS(float4 Position : SV_POSITION0, float4 Color : COLOR0)
//{
//    PixelInput output;
//    output.Position = input.Position;
//    output.Color = input.Color;

//    return output;
//}

// VS�� �Լ��� �������̸��̴�.(�������̸��� ������� �ᵵ �ȴ�)

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = input.Position;
    output.Color = input.Color;

    return output;
}

// PS���� float4�� RGBA �ϳ��� �ȼ����� ��ȯ���ش�.
// �ȼ��� �������� �ȼ��� �׸� Ÿ�� �� ��ȭ���� �ݵ�� �ʿ��ϴ�.
// �׷��Ƿ� SV�� �ٿ��ش�.

float4 PS(PixelInput input) : SV_TARGET
{
    return input.Color;
}