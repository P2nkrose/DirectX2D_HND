#ifndef _POSTPROCESS
#define POSTPROCESS

#include "value.fx"

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};


struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};


// ============================
// Gray Filter Shader

// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// g_tex_1  : NoiseTexture 1
// g_tex_2  : NoiseTexture 2
// g_tex_3  : NoiseTexture 3
// =============================

VS_OUT VS_GrayFilter(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // Proj ����� ���� ����� �� xyz �� �ڽ��� ViewZ �� ������ �ִ� �����̴�.
    // W �ڸ��� �ڽ��� ViewZ �� ��µǱ� ������ �̰����� �� xyz �� ������� ���� Proj ��ǥ�� ���´�.
    // ���� Rasterizer State �� ��������� ���� ����� �����ϸ� �� xyz �� w �� ����� ����Ѵ�.
    // ���� ���� ������ ������ w ���� 1�� �־��൵ ������ 1�� �����ָ� �ƹ� ȿ���� ���⶧���� 1�� �����Ѵ�.
    
    output.vPosition = float4(_in.vPos.xy * 2.f, 0.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_GrayFilter(VS_OUT _in) : SV_Target
{
    // Gray Filter
    //float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    //float Average = (vColor.x + vColor.y + vColor.z) / 3.f;
    //vColor = float4(Average, Average, Average, 1.f);
    
    // Cos Distortion
    //float2 vUV = _in.vUV;
    //vUV.y += cos((vUV.x + g_EngineTime * 0.1f) * PI * 12.f) * 0.01;
    //float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
    
    // Noise
    float2 vUV = _in.vUV;
    vUV.x += g_EngineTime * 0.1;
    
    float4 vNoise = g_tex_1.Sample(g_sam_0, vUV);
    
    vNoise = (vNoise * 2.f - 1.f) * 0.01f;
    
    vUV = _in.vUV + vNoise.xy;
    float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
    
    //vColor.b *= 1.5f;
    
    return vColor;
}



// ============================
// Distortion Shader

// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// g_tex_1  : NoiseTexture 1
// g_tex_2  : NoiseTexture 2
// g_tex_3  : NoiseTexture 3
// =============================

VS_OUT VS_Distortion(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Distortion(VS_OUT _in) : SV_Target
{
    // 1. ����Ÿ�� �ػ� ���� (���� �������)
    // 2. �ȼ� ���̴��� �ȼ� ��ǥ
    float2 vScreenUV = _in.vPosition.xy / g_Resolution;
    
    float2 vNoiseUV = vScreenUV;
    vNoiseUV.x += g_EngineTime * 0.1;
    float4 vNoise = g_tex_3.Sample(g_sam_0, vNoiseUV);
    
    vNoise = (vNoise * 2.f - 1.f) * 0.01f;
    vScreenUV = vScreenUV + vNoise.xy;
    float4 vColor = g_tex_0.Sample(g_sam_0, vScreenUV);
   
    
    // ĳ���� �ӵ� ü��
    //float2 vScreenUV = _in.vPosition.xy / g_Resolution;
    //
    //float2 vNoiseUV = vScreenUV;
    ////vNoiseUV.y += g_EngineTime * 0.5;
    //vNoiseUV.y += tan((vNoiseUV.y + g_EngineTime * 0.9f) * PI * 12.f) * 0.01;
    //float4 vNoise = g_tex_4.Sample(g_sam_0, vNoiseUV);
    //
    //vNoise = (vNoise * 2.f - 1.f) * 0.01f;
    //vScreenUV = vScreenUV + vNoise.xy;
    //float4 vColor = g_tex_0.Sample(g_sam_0, vScreenUV);
    
   
    // Ƽ��ȭ�� ������
    //float2 vScreenUV = _in.vPosition.xy / g_Resolution;
    //
    //float2 vNoiseUV = vScreenUV;
    ////vNoiseUV.y += g_EngineTime * 0.3;
    //vNoiseUV.y += tan((vNoiseUV.y + g_EngineTime * 0.1f) * PI * 5.f) * 0.01;
    //float4 vNoise = g_tex_5.Sample(g_sam_0, vNoiseUV);
    //
    //vNoise = (vNoise * 2.f - 1.f) * 0.01f;
    //vScreenUV = vScreenUV + vNoise.xy;
    //float4 vColor = g_tex_0.Sample(g_sam_0, vScreenUV);
    
    
    
    // ��Ż �տ� ��������
    //float2 vScreenUV = _in.vPosition.xy / g_Resolution;
    //
    //float2 vNoiseUV = vScreenUV;
    //vNoiseUV.x += g_EngineTime * 0.5;
    //vNoiseUV.y += tan((vNoiseUV.y + g_EngineTime * 0.1f) * PI * 5.f) * 0.01;
    //float4 vNoise = g_tex_2.Sample(g_sam_0, vNoiseUV);
    //
    //vNoise = (vNoise * 2.f - 1.f) * 0.01f;
    //vScreenUV = vScreenUV + vNoise.xy;
    //float4 vColor = g_tex_0.Sample(g_sam_0, vScreenUV);
   
    
    
    
    
    
    
    return vColor;
}
#endif