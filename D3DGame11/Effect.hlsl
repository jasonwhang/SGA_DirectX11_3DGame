// Vertex Shader가 받을 정보
// 공간 변환을 해준다.
// 정점이 들어간 갯수만큼 정점쉐이더가 돈다(여기서는 정점이 6개 생성했으므로 6번 호출한다)

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

// 원래는 이 방법이 맞다.
//PixelInput VS(float4 Position : SV_POSITION0, float4 Color : COLOR0)
//{
//    PixelInput output;
//    output.Position = input.Position;
//    output.Color = input.Color;

//    return output;
//}

// VS는 함수의 진입점이름이다.(진입점이름은 마음대로 써도 된다)

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = input.Position;
    output.Color = input.Color;

    return output;
}

// PS에서 float4는 RGBA 하나의 픽셀값을 반환해준다.
// 픽셀을 찍을려면 픽셀을 그릴 타겟 즉 도화지가 반드시 필요하다.
// 그러므로 SV를 붙여준다.

float4 PS(PixelInput input) : SV_TARGET
{
    return input.Color;
}