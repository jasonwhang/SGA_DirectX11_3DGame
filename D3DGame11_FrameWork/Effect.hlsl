// Vertex Shader가 받을 정보
// 공간 변환을 해준다.
// 정점이 들어간 갯수만큼 정점쉐이더가 돈다(여기서는 정점이 6개 생성했으므로 6번 호출한다)

// cbuffer : constant buffer
// register(등록)
// b : buffer
// t : texture
cbuffer WorldViewProjectionBuffer : register(b0)
{
    //float4x4 = matrix(같은 말이다)

    matrix World;
    matrix View;
    matrix Projection;
};

struct VertexInput
{
	// HLSL은 기본적으로 float 자료형밖에 사용을 할 수가 없다
	float4 Position : POSITION0;
	float4 Color : COLOR0;
};

struct PixelInput
{
	// SV => System Value;
	// SV는 무조건 써야하는 값에 사용한다.

    float4 Position : SV_POSITION0;
    float4 Color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    // GPU가 계산이 더 빠르다.
    // CPU에서 계산을 다 하고 Shader에 넘겨줘도 되긴하다.

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