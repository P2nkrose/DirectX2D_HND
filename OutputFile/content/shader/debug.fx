#ifndef _DEBUG_SHADER
#define _DEBUG_SHADER

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

VS_OUT VS_DebugShape(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_DebugShape(VS_OUT _in) : SV_Target
{
    //if(g_int_1)
    //{
    //    if (g_float_0 <= _in.vUV.x && _in.vUV.x <= (1.f - g_float_0)
    //        && g_float_0 <= _in.vUV.y && _in.vUV.y <= (1.f - g_float_0))
    //    {
    //        discard;
    //    }
    //}
    //else
    //{
    //    float fDist = distance(float2(0.5f, 0.5f), _in.vUV);
    //    if (fDist < 0.5f - g_float_0)
    //        discard;
    //}
    
    return g_vec4_0;
}

#endif