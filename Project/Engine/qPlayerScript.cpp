#include "pch.h"

#include "qPlayerScript.h"
#include "qMissileScript.h"

qPlayerScript::qPlayerScript()
	: m_Speed(500.f)
{
}

qPlayerScript::~qPlayerScript()
{
}

void qPlayerScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();
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
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1);
		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.z += DT * XM_PI;
		Transform()->SetRelativeRotation(vRot);


		//Vec3 vScale = Transform()->GetRelativeScale();
		//vScale += DT * 100.f * Vec3(1.f, 1.f, 1.f);
		//Transform()->SetRelativeScale(vScale);
	}
	else
	{
		//MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		// 미사일 발사
		qGameObject* pMissileObject = new qGameObject;
		pMissileObject->AddComponent(new qTransform);
		pMissileObject->AddComponent(new qMeshRender);
		pMissileObject->AddComponent(new qCollider2D);
		pMissileObject->AddComponent(new qMissileScript);

		Vec3 vMissilePos = Transform()->GetRelativePos();
		vMissilePos.y += Transform()->GetRelativeScale().y / 2.f;

		pMissileObject->Transform()->SetRelativePos(vMissilePos);
		pMissileObject->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

		pMissileObject->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

		CreateObject(pMissileObject, 5);
	}


	Transform()->SetRelativePos(vPos);
}


void qPlayerScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	DeleteObject(_OtherObject);

	Vec3 vScale = Transform()->GetRelativeScale();

	vScale += Vec3(10.f, 10.f, 0.f);
	Collider2D()->SetScale(Collider2D()->GetScale() + Vec3(10.f, 10.f, 0.f));

	Transform()->SetRelativeScale(vScale);
}
