cbuffer OBUFFER : register (b0)
{
	float4x4 worldM;
}
cbuffer CBUFFER : register (b1)
{
	float4x4 viewM;
	float4x4 projM;
}

struct GS_IN
{
	float4 Pos	: SV_POSITION;
	float3 Norm	: NORMAL;
	float2 uv	: UV;
};

struct GS_OUT
{
	float4 Pos	: SV_POSITION;
	float4 Norm	: NORMAL;
	float2 uv	: UV;
	float4 wPos : POSITION;
};

[maxvertexcount(6)]
void GS_main(triangle GS_IN input[3], inout TriangleStream <GS_OUT> outputStream)
{
	GS_OUT output = (GS_OUT)0;

	for (int i = 0; i < 3; i++)
	{
		output.Pos = mul(mul(mul(input[i].Pos, worldM), viewM), projM);
		output.Norm = float4(input[i].Norm, 1.0f);
		output.uv = input[i].uv;
		output.wPos = mul(input[i].Pos, worldM);

		outputStream.Append(output);
	}
}