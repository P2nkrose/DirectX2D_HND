#pragma once
#include "qEntity.h"

enum class BB_DATA
{
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    OBJECT,
};

struct tBlackboardData
{
    BB_DATA     Type;
    void*       pData;
};

class qBlackboard : public qEntity
{
public:
    CLONE(qBlackboard);
    qBlackboard();
    qBlackboard(const qBlackboard& _board);
    ~qBlackboard();


public:
    void GetBlackboardData(const wstring* _strKey);
    void AddBlackboardData(const wstring& _strKey);


private:
    map<wstring, tBlackboardData>       m_mapBBData;
};

