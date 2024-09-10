#include "pch.h"
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

#include "qCrashScript.h"
#include "qSkeletonScript.h"
#include "qPlayerEffectScript.h"
#include <States/qPlayerEffectState.h>

qCrashScript::qCrashScript()
	: qScript((UINT)SCRIPT_TYPE::CRASHSCRIPT)
	, m_CrashDamage(30.f)
{
}

qCrashScript::~qCrashScript()
{
}

void qCrashScript::Begin()
{
}

void qCrashScript::Tick()
{
}

void qCrashScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	Vec3 CrashPos = GetOwner()->Transform()->GetRelativePos();
	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DMtrl");
	Ptr<qMaterial> pAlphaBlendMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"Std2DAlphaBlendMtrl");
	Ptr<qMaterial> pDebugShapeMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"DebugShapeMtrl");

	if (GetOwner() != nullptr)
	{
		if (_OtherObject->GetName() == L"Skeleton")
		{
			qSkeletonScript* SkeletonScript = _OtherObject->GetScript<qSkeletonScript>();

			if (SkeletonScript == nullptr)
				return;

			SkeletonScript->Hit(m_CrashDamage);
		}


		if (_OtherObject->GetName() == L"Skeleton")
		{
			qGameObject* Effect = new qGameObject;
			Effect->SetName(L"effect");
			Effect->AddComponent(new qPlayerEffectScript);
			Effect->AddComponent(new qTransform);
			Vec3 MonsterPos = _OtherObject->Transform()->GetRelativePos();
			Vec3 MonsterScale = _OtherObject->Transform()->GetRelativeScale();
			Effect->Transform()->SetRelativePos(Vec3(MonsterPos.x - (MonsterScale.x * 0.5f), MonsterPos.y, MonsterPos.z));
			Effect->Transform()->SetRelativeScale(180.f, 180.f, 1.f);

			Effect->AddComponent(new qMeshRender);
			Effect->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
			Effect->MeshRender()->SetMaterial(pAlphaBlendMtrl);

			Effect->AddComponent(new qFlipBookComponent);
			Ptr<qFlipBook> pEffect = qAssetMgr::GetInst()->FindAsset<qFlipBook>(L"Animation\\effect.flip");
			Effect->FlipBookComponent()->AddFlipBook(0, pEffect);

			Effect->AddComponent(new qFSM);
			Effect->FSM()->AddState(L"Effect", new qPlayerEffectState);

			Effect->FSM()->ChangeState(L"Effect");

			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(12, Effect);
		}


	}

}

void qCrashScript::SaveToFile(FILE* _File)
{
}

void qCrashScript::LoadFromFile(FILE* _File)
{
}
