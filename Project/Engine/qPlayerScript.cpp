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
		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += XM_PI * DT;
		Transform()->SetRelativeRotation(vRot);
	}


	Transform()->SetRelativePos(vPos);
}
