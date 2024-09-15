#include "pch.h"
#include "qGhostDeathState.h"

#include <Scripts/qGhostScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>
#include <Scripts/qDeathSoulScript.h>
#include <States/qDeathSoulState.h>

qGhostDeathState::qGhostDeathState()
	: qState((UINT)STATE_TYPE::GHOSTDEATHSTATE)
{
}

qGhostDeathState::~qGhostDeathState()
{
}

void qGhostDeathState::Enter()
{
	OGScale = GetOwner()->Transform()->GetRelativeScale();
	OGColScale = GetOwner()->Collider2D()->GetScale();

	GetOwner()->Transform()->SetRelativeScale(250.f, 260.f, 10.f);
	GetOwner()->Collider2D()->SetScale(Vec3(0.001f, 0.001f, 1.f));

	GetOwner()->FlipBookComponent()->Play(5, 8, false);

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Hitbox = pCurLevel->FindObjectByName(L"GhostAttackHitbox");

	if (Hitbox != nullptr)
		Hitbox->Destroy();
}

void qGhostDeathState::FinalTick()
{
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");


	if (GetOwner()->FlipBookComponent()->IsCurFlipBookFinished())
	{
		GetOwner()->Destroy();
	}

	// Death Soul ����
	static bool flag = false;

	if (!flag)
	{
		qGameObject* DeathSoul = new qGameObject;
		DeathSoul->SetName(L"deathsoul");
		DeathSoul->AddComponent(new qDeathSoulScript);
		DeathSoul->AddComponent(new qTransform);
		Vec3 MonsterPos = GetOwner()->Transform()->GetRelativePos();
		Vec3 MonsterScale = GetOwner()->Transform()->GetRelativeScale();

		DeathSoul->Transform()->SetRelativePos(Vec3(MonsterPos.x, MonsterPos.y + 300.f/*(MonsterScale.y * 0.5f)*/, MonsterPos.z));
		DeathSoul->Transform()->SetRelativeScale(800.f, 800.f, 1.f);

		DeathSoul->AddComponent(new qMeshRender);
		DeathSoul->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
		DeathSoul->MeshRender()->SetMaterial(pAlphaBlendMtrl);

		DeathSoul->AddComponent(new qFlipBookComponent);
		Ptr<qFlipBook> pDeathSoul = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\deathsoul.flip");
		DeathSoul->FlipBookComponent()->AddFlipBook(0, pDeathSoul);

		DeathSoul->AddComponent(new qFSM);
		DeathSoul->FSM()->AddState(L"DeathSoul", new qDeathSoulState);

		DeathSoul->FSM()->ChangeState(L"DeathSoul");

		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(12, DeathSoul);


		flag = true;
	}
}

void qGhostDeathState::Exit()
{
	GetOwner()->Transform()->SetRelativeScale(OGScale);
	GetOwner()->Collider2D()->SetScale(OGColScale);
}
