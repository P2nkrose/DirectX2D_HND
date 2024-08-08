#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"
#include "struct.fx"

RWStructuredBuffer<tParticle> ParticleBuffer : register(u0);
RWStructuredBuffer<tSpawnCount> SpawnCountBuffer : register(u1);

#define MAX_COUNT       g_int_0
#define Particle        ParticleBuffer[_ID.x]

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
                break;
            }
            
            SpawnCount = SpawnCountBuffer[0].iSpawnCount;
        }
    }
    
    else
    {
        Particle.vWorldPos += Particle.vVelocity * g_EngineDT;
    }
    
}

// 1. ��ƼŬ ������, ��Ȱ��ȭ ��ƼŬ ó�� + ������

// 2. ��ƼŬ ����ȭ

// 3. ��ƼŬ CS ���� ����



#endif