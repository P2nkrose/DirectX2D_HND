#ifndef _TILEMAP
#define _TILEMAP

#include "value.fx"

struct tTileInfo
{
    uint ImgIdx;
    int3 Padding;
};


// ===============================
// TileMapShader
// parameter
#define AtlasTex        g_tex_0
#define IsAtlasBind     g_btex_0
#define AtlasMaxRow     g_int_1
#define AtlasMaxCol     g_int_2
#define TileSliceUV     g_vec2_0
#define TileColRow      g_vec2_1
StructuredBuffer<tTileInfo> g_Buffer : register(t15);
// ===============================



struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV  : TEXCOORD;
};


struct VS_OUT
{
    float4 vPosition    : SV_Position;
    float2 vUV          : TEXCOORD;
    
    float3 vWorldPos    : POSITION;
};

VS_OUT VS_TileMap(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // TileMap �� ���� �ϴ����� Ȯ��ǵ��� �ϱ� ���ؼ� 
    // Local RectMesh �� ��ǥ�� ������ �� ��������� ���ϰ� �Ѵ�.
    _in.vPos.x += 0.5f;
    _in.vPos.y -= 0.5f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), matWVP);
    output.vUV = _in.vUV * TileColRow;
    output.vWorldPos = mul(float4(_in.vPos, 1.f), matWorld);
    
    
    return output;
}


float4 PS_TileMap(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (IsAtlasBind)
    {
        // �ȼ����̴����� ������ Ÿ���� ���° Ÿ������ �˾Ƴ��� �Ѵ�.
        float2 CurColRow = floor(_in.vUV);
        int Idx = TileColRow.x * CurColRow.y + CurColRow.x;
        
        // �� ������ g_Buffer �� ���޵� �� Ÿ������ �� ������ ������ �����ؼ� ImgIdx �� �˾Ƴ���.
        // �˾Ƴ� ImgIdx �� LeftTopUV ���� ����Ѵ�.
        
        int row = g_Buffer[Idx].ImgIdx / AtlasMaxCol;
        int col = g_Buffer[Idx].ImgIdx % AtlasMaxCol;
        float2 vLeftTopUV = float2(col, row) * TileSliceUV;
        
        float2 vUV = vLeftTopUV + frac(_in.vUV) * TileSliceUV;
        vOutColor = AtlasTex.Sample(g_sam_1, vUV);
    }
    else
    {
        vOutColor = float4(1.f, 0.f, 1.f, 1.f);
    }
    
    
    // ���� ����
    // DirectionalLight �� ���
    if(0 == g_Light2D[0].Type)
    {
        vOutColor.rgb = g_Light2D[0].light.Color.rgb * vOutColor.rgb
                      + g_Light2D[0].light.Ambient.rgb * vOutColor.rgb;
    }
    else if(1 == g_Light2D[0].Type)
    {
         // �������� �ȼ������� �Ÿ�
        float fDist = distance(g_Light2D[0].WorldPos.xy, _in.vWorldPos.xy);
        
        // �Ÿ����� ������ ġȯ�ؼ� �Ÿ��� ���� ���� ���⸦ �ڻ��� �׷��� ���·� ����Ѵ�.
        float fPow = cos(saturate((fDist / g_Light2D[0].Radius)) * (PI / 2.f));
        
        // �������κ��� ������ �Ÿ��� ���� ���� ����
        //float fPow2 = saturate(1.f - fDist / g_Light2D[0].Radius);
        
        // ���� ���� ��� = ��ü�� * ���� �� * �Ÿ������� ����
        vOutColor.rgb = vOutColor.rgb * g_Light2D[0].light.Color.rgb * fPow;
    }
   
    return vOutColor;
}


#endif