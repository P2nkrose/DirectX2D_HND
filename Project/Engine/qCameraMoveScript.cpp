#include "pch.h"
#include "qCameraMoveScript.h"

qCameraMoveScript::qCameraMoveScript()
	: m_CamSpeed(500.f)
{
}

qCameraMoveScript::~qCameraMoveScript()
{
}

void qCameraMoveScript::Tick()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}


	Vec3 vFront = Transform()->GetDir(DIR::FRONT);
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::Y))
	{
		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += XM_PI * DT;
		Transform()->SetRelativeRotation(vRot);
	}

	Transform()->SetRelativePos(vPos);

}
