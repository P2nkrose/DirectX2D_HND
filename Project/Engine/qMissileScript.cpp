#include "pch.h"
#include "qMissileScript.h"

qMissileScript::qMissileScript()
	: m_Speed(1000.f)
{
}

qMissileScript::~qMissileScript()
{
}

void qMissileScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos.y += DT * m_Speed;

	Transform()->SetRelativePos(vPos);
}

void qMissileScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	
}
