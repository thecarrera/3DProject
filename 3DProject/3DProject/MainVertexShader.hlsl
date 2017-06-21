struct VS_IN
{
	float3 Pos	: SV_POSITION;
	float3 Norm	: NORMAL;
	float2 uv	: UV;
};

struct VS_OUT
{
	float4 Pos	: SV_POSITION;
	float3 Norm : NORMAL;
	float2 uv	: UV;
};

VS_OUT VS_main(  VS_IN input )
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = float4(input.Pos, 1.0f);
	output.Norm = input.Norm;
	output.uv = input.uv;

	return output;
}