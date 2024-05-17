// C ��Ÿ���� #pragma once
#ifndef _TEST
#define _TEST

cbuffer OBJECT_POS : register(b0)
{
    row_major matrix matWorld;
}

// Vertex Shader
struct VTX_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    // LocalSpace �� WorldSpace
    // float3 x float4x4(matrix)
    // float3 �� float4 �� ������ ���߾� �ش�.
    // ������ǥ�� 1 �� ����, ������� 4�࿡ ����ִ� �̵��� ����ްڴٴ� ��
    
    output.vPosition = mul(float4(_in.vPos, 1.f), matWorld);
    output.vColor = _in.vColor;
    
    return output;
}


float4 PS_Test(VTX_OUT _in) : SV_Target
{
    return _in.vColor;
}

#endif