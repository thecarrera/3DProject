cbuffer LBUFFER : register (b0)
{
	float4 lightPos;
}

struct FS_IN
{
	float4 Pos	: SV_POSITION;
	float4 Norm : NORMAL;
	float2 uv	: UV;
	float4 wPos : POSITION;
};

float4 FS_main(FS_IN input) : SV_Target
{
	float3 lightDir = normalize(lightPos.xyz - input.wPos.xyz);
	float cos = dot(lightDir, input.Norm.xyz);

	return cos * float4(1.0f, 1.0f, 1.0f, 1.0f);
}