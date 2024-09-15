#include "pch.h"
#include "qSkeletonIdleState.h"

#include <Scripts/qSkeletonScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>


qSkeletonIdleState::qSkeletonIdleState()
	: qState((UINT)STATE_TYPE::SKELETONIDLESTATE)
	, m_DetectRange(220.f)
	, m_Bang(nullptr)
	, m_BangTime(0.f)
	, Bangflag(false)
{
}

qSkeletonIdleState::~qSkeletonIdleState()
{
}

void qSkeletonIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);

}

void qSkeletonIdleState::FinalTick()
{
	Ptr<qMaterial> pBangMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\bang.mtrl");

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	Vec3 SkeletonPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();

	Vec3 Dir = PlayerPos - SkeletonPos;

	float Dist = Dir.Length();

	Bangflag = false;

	if (Dist < m_DetectRange && !Bangflag)
	{
		// 느낌표 생성
		m_Bang = new qGameObject;
		m_Bang->SetName(L"SkeletonBang");

		m_Bang->AddComponent(new qMeshRender);
		m_Bang->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
		m_Bang->MeshRender()->SetMaterial(pBangMtrl);

		m_Bang->AddComponent(new qTransform);
		m_Bang->Transform()->SetRelativePos(SkeletonPos.x, SkeletonPos.y + 150.f, 5.f);
		m_Bang->Transform()->SetRelativeScale(25.f, 80.f, 1.f);

		pCurLevel->AddObject(12, m_Bang);

		Bangflag = true;
	}



	if (Dist < m_DetectRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qSkeletonScript>()->GetSkeletonDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"SkeletonAttack");
		}

	}


}

void qSkeletonIdleState::Exit()
{
	Bangflag = false;
}
