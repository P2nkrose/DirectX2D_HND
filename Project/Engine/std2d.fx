// C 스타일의 #pragma once
#ifndef _TEST
#define _TEST

#include "value.fx"
#include "func.fx"

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

VTX_OUT VS_Std2D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    // LocalSpace → WorldSpace
    // float3 x float4x4(matrix)
    // float3 을 float4 로 차수를 맞추어 준다.
    // 동차좌표를 1 로 설정, 상태행렬 4행에 들어있는 이동을 적용받겠다는 뜻
    
    output.vPosition = mul(float4(_in.vPos, 1.f), matWVP);
    
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}


float4 PS_Std2D(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
         
    // FlipBook 을 사용한다.
    if (g_int_0)
    {
        // _in.vUV : 스프라이를 참조할 위치를 비율로 환산한 값
        float2 vSpriteUV = g_vec2_0 /*LeftTop*/ + (_in.vUV * g_vec2_1 /*Slice*/);
        vColor = g_AtlasTex.Sample(g_sam_1, vSpriteUV);
    }
    // FlipBook 을 사용하지 않는다.
    else
    {
        if (g_btex_0)
        {
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        }
        else
        {
            vColor = float4(1.f, 0.f, 1.f, 1.f);
        }
    }

    if (vColor.a == 0.f)
    {
        //clip(-1);
        discard;
    }
        return vColor;
}



float4 PS_Std2D_Alphablend(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    if(g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    }
    else
    {
        vColor = float4(1.f, 0.f, 1.f, 1.f);
    }
    
    return vColor;
}


#endif