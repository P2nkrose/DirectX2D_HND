#include "pch.h"
#include "qPlayerKrushState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qKrushScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerKrushState::qPlayerKrushState()
	: m_KrushSpeed(1200.f)
{
}

qPlayerKrushState::~qPlayerKrushState()
{
}

void qPlayerKrushState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(700.f, 700.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.19f, 0.19f, 0.f));

	GetOwner()->FlipBookComponent()->Play(21, 15, false);

}

void qPlayerKrushState::FinalTick()
{
	qPlayerScript* pPlayerScript = GetOwner()->GetScript<qPlayerScript>();

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"stage1")
	{
		Vec3 PlayerPos = GetOwner()->Transform()->GetRelativePos();

		if (PlayerPos.y <= -420.f)
		{
			PlayerPos.y = -420.f;
		}
		else
		{
			PlayerPos += Vec3(0.f, -1.2f, 0.f) * m_KrushSpeed * DT;
		}

		GetOwner()->Transform()->SetRelativePos(PlayerPos);
	}

	static bool hitboxCreated = false; // ��Ʈ�ڽ� ���� ���θ� �����ϴ� �÷���

	// ��Ʈ�ڽ� ����
	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 4 && !hitboxCreated)
	{
		// ��Ʈ�ڽ� ����
		Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
		qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
		qPlayerScript* pPlayerScript = pPlayer->GetScript<qPlayerScript>();
		Vec3 vPlayerPos = pPlayer->Transform()->GetRelativePos();

		KrushHitBox = new qGameObject;
		KrushHitBox->SetName(L"KrushHitBox");
		KrushHitBox->AddComponent(new qKrushScript);
		KrushHitBox->AddComponent(new qTransform);
		KrushHitBox->Transform()->SetRelativeScale(150.f, 150.f, 1.f);

		KrushHitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z));


		KrushHitBox->AddComponent(new qCollider2D);
		KrushHitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));

		pCurLevel->AddObject(4, KrushHitBox);
		hitboxCreated = true; // ��Ʈ�ڽ��� �����Ǿ����� ǥ��
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (KrushHitBox != nullptr)
		{
			KrushHitBox->Destroy();
			KrushHitBox = nullptr;
			hitboxCreated = false;	// ���� ���� ��ȯ �ø� ���� �÷��� �ʱ�ȭ
		}

		if(pPlayerScript->RigidBody()->IsGround())
			ChangeState(L"Idle");
	}

	//if (pPlayerScript->RigidBody()->IsGround() && GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	//{
	//	ChangeState(L"Idle");
	//}

}

void qPlayerKrushState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
