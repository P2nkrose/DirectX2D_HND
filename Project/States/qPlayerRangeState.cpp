#include "pch.h"
#include "qPlayerRangeState.h"

#include <Engine/qFlipBookComponent.h>
#include <Engine/qGameObject.h>
#include <Scripts/qPlayerScript.h>
#include <Scripts/qRangeScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qPlayerRangeState::qPlayerRangeState()
{
}

qPlayerRangeState::~qPlayerRangeState()
{
}

void qPlayerRangeState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(600.f, 600.f, 0.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.22f, 0.22f, 0.f));

	GetOwner()->FlipBookComponent()->Play(20, 15, false);



	// ��Ʈ�ڽ� ����
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	qGameObject* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	qPlayerScript* pPlayerScript = pPlayer->GetScript<qPlayerScript>();
	Vec3 vPlayerPos = pPlayer->Transform()->GetRelativePos();

	RangeHitBox = new qGameObject;
	RangeHitBox->SetName(L"RangeHitBox");
	RangeHitBox->AddComponent(new qRangeScript);
	RangeHitBox->AddComponent(new qTransform);
	RangeHitBox->Transform()->SetRelativeScale(230.f, 260.f, 1.f);

	RangeHitBox->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y + 60.f, vPlayerPos.z));


	RangeHitBox->AddComponent(new qCollider2D);
	RangeHitBox->Collider2D()->SetScale(Vec3(1.f, 1.f, 1.f));
}

void qPlayerRangeState::FinalTick()
{
	static bool hitboxCreated = false; // ��Ʈ�ڽ� ���� ���θ� �����ϴ� �÷���

	// ��Ʈ�ڽ� ����
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (GetOwner()->FlipBookComponent()->GetCurFrmIdx() == 5 && !hitboxCreated)
	{
		pCurLevel->AddObject(4, RangeHitBox);
		hitboxCreated = true; // ��Ʈ�ڽ��� �����Ǿ����� ǥ��
	}

	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		if (RangeHitBox != nullptr)
		{
			RangeHitBox->Destroy();
			RangeHitBox = nullptr;
			hitboxCreated = false;	// ���� ���� ��ȯ �ø� ���� �÷��� �ʱ�ȭ
		}

		ChangeState(L"Idle");
	}
}

void qPlayerRangeState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
