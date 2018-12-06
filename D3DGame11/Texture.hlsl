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

// t0 : Texture0라는 의미이다.
// Diffuse : 내가 가지고 있는 색을 발산하는 것(원래는 빛에 의해 반사된 색이 망막에 비쳐 보이는 것이지만 컴퓨터에는 빛이 없기 때문에 자기 색을 발산한다.)
Texture2D DiffuseMap : register(t0);
// 이 텍스쳐를 그릴때 어떤 식으로 붙이고 어떤 식으로 표시할 것인지를 알려주는 것(Rasterize와 비슷하다)
SamplerState DiffuseSamp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    return DiffuseMap.Sample(DiffuseSamp, input.UV);
}