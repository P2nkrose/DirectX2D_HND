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
	if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
	{
		OrthoGraphicMove();
	}
	else if (PROJ_TYPE::PERSPECTIVE == Camera()->GetProjType())
	{
		PerspectiveMove();
	}


	// ������� ��ȯŰ
	if (KEY_TAP(KEY::P))
	{
		if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
		{
			Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		}
		else
		{
			Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		}
	}

}

void qCameraMoveScript::OrthoGraphicMove()
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
		vPos.y += DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * Speed;
	}

	Transform()->SetRelativePos(vPos);
}

void qCameraMoveScript::PerspectiveMove()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}


	Vec3 vFront = Transform()->GetDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetDir(DIR::RIGHT);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront* DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= vRight * DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += vRight * DT * Speed;
	}

	Transform()->SetRelativePos(vPos);


	if (KEY_PRESSED(KEY::RBTN))
	{
		qKeyMgr::GetInst()->MouseCapture(true);

		// ���콺�� �̵��ϴ� ����
		// vDir.x; ==>  y�� ȸ��
		// vDir.y; ==>  x�� ȸ��
		Vec2 vDir = qKeyMgr::GetInst()->GetDragDir();

		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += vDir.x * XM_PI * DT * 10.f;
		vRot.x += vDir.y * XM_PI * DT * 10.f;
		Transform()->SetRelativeRotation(vRot);
	}
	else if (KEY_RELEASED(KEY::RBTN))
	{
		qKeyMgr::GetInst()->MouseCapture(false);
	}


}