// C ��Ÿ���� #pragma once
#ifndef _TEST
#define _TEST

cbuffer OBJECT_POS : register(b0)
{
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProj;
    
}

SamplerState g_sam_0 : register(s0);

Texture2D g_tex_0 : register(t0);

// Vertex Shader
struct VTX_IN
{
    float3 vPos         : POSITION;
    float4 vColor       : COLOR;
    float2 vUV          : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition    : SV_Position;
    float4 vColor       : COLOR;
    float2 vUV          : TEXCOORD;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    // LocalSpace �� WorldSpace
    // float3 x float4x4(matrix)
    // float3 �� float4 �� ������ ���߾� �ش�.
    // ������ǥ�� 1 �� ����, ������� 4�࿡ ����ִ� �̵��� ����ްڴٴ� ��
    
    float3 vWorldPos = mul(float4(_in.vPos, 1.f), matWorld);
    float4 vViewPos = mul(float4(vWorldPos, 1.f), matView);
    float4 vProjPos = mul(vViewPos, matProj);
    
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}


float4 PS_Test(VTX_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    vColor.a = 0.f;
    return _in.vColor;
}

#endif