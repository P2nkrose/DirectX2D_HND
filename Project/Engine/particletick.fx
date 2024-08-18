#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"
#include "struct.fx"

RWStructuredBuffer<tParticle>   ParticleBuffer : register(u0);
RWStructuredBuffer<tSpawnCount> SpawnCountBuffer : register(u1);
Texture2D                       NoiseTex : register(t20);

#define ParticleObjectPos   g_vec4_0.xyz
#define MAX_COUNT           g_int_0
#define Particle            ParticleBuffer[_ID.x]

[numthreads(1024, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    if(MAX_COUNT <= _ID.x)
        return;
    
    if(false == Particle.Active)
    {
        int SpawnCount = SpawnCountBuffer[0].iSpawnCount;
        
        while(0 < SpawnCount)
        {
            int Origin = 0;
            
            //InterlockedExchange(SpawnCountBuffer[0].iSpawnCount
            //                  , SpawnCountBuffer[0].iSpawnCount - 1
            //                  , Origin);
            
            InterlockedCompareExchange(SpawnCountBuffer[0].iSpawnCount
                                     , SpawnCount
                                     , SpawnCountBuffer[0].iSpawnCount - 1
                                     , Origin);
            
            if(SpawnCount == Origin)
            {
                Particle.Active = true;
                
                // ��ƼŬ�� ��ġ�� Ư�� ���������� ������ ��ġ�� ����ش�.
                float2 vUV = (float2) 0.f;
                
                // �����带 UV�� �����ϱ� ���ؼ� ID �� 0 ~ 1 ������ ����ȭ
                vUV.x = ((float) _ID.x / (float)(MAX_COUNT - 1)) + g_EngineTime * 0.5f;
                vUV.y = sin(vUV.x * 20 * PI) * 0.5f + g_EngineTime * 0.1f;
                
                float3 vNoise = NoiseTex.SampleLevel(g_sam_1, vUV, 0).xyz;
                
                float BoxScale = 300.f;
                
                float3 vRandomPos = (float3) 0.f;
                
                vRandomPos.x = vNoise.x * BoxScale - (BoxScale / 2.f);
                vRandomPos.y = vNoise.y * BoxScale - (BoxScale / 2.f);
                vRandomPos.z = vNoise.z * BoxScale - (BoxScale / 2.f);
                
                Particle.vLocalPos = vRandomPos;
                Particle.vWorldPos = Particle.vLocalPos + ParticleObjectPos;
                Particle.Active = true;
                Particle.Age = 0.f;
                Particle.Life = 2.f;
                Particle.NormalizedAge = 0.f;
                
                break;
            }
            
            SpawnCount = SpawnCountBuffer[0].iSpawnCount;
        }
    }
    
    else
    {
         Particle.vWorldPos += Particle.vVelocity * g_EngineDT;
        
        Particle.Age += g_EngineDT;
        if (Particle.Life <= Particle.Age)
        {
            Particle.Active = false;
        }
    }
    
}

// 1. ��ƼŬ ������, ��Ȱ��ȭ ��ƼŬ ó�� + ������

// 2. ��ƼŬ ����ȭ

// 3. ��ƼŬ CS ���� ����



#endif