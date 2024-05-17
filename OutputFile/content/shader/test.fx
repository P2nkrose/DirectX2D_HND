// C 스타일의 #pragma once
#ifndef _TEST
#define _TEST

cbuffer OBJECT_POS : register(b0)
{
    row_major matrix matWorld;
    row_major matrix matView;
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
    
    // LocalSpace → WorldSpace
    // float3 x float4x4(matrix)
    // float3 을 float4 로 차수를 맞추어 준다.
    // 동차좌표를 1 로 설정, 상태행렬 4행에 들어있는 이동을 적용받겠다는 뜻
    
    float3 vWorldPos = mul(float4(_in.vPos, 1.f), matWorld);
    float4 vViewPos = mul(float4(vWorldPos, 1.f), matView);
    
    output.vPosition = vViewPos;
    output.vColor = _in.vColor;
    
    return output;
}


float4 PS_Test(VTX_OUT _in) : SV_Target
{
    return _in.vColor;
}

#endif