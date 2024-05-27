#include "pch.h"
#include "qPlayerScript.h"

qPlayerScript::qPlayerScript()
	: m_Speed(500.f)
{
}

qPlayerScript::~qPlayerScript()
{
}

void qPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::UP))
	{
		vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vScale = Transform()->GetRelativeScale();
		vScale.x += DT * 100.f;
		vScale.y += DT * 100.f;
		Transform()->SetRelativeScale(vScale);

		//Vec3 vRot = Transform()->GetRelativeRoatation();
		//vRot.y += XM_PI * DT;
		//Transform()->SetRelativeRotation(vRot);
	}


	Transform()->SetRelativePos(vPos);
}
