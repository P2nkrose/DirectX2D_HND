#include "pch.h"
#include "qDrownedIdleState.h"

#include <Scripts/qDrownedScript.h>
#include <Engine/qLevel.h>
#include <Engine/qLevelMgr.h>

qDrownedIdleState::qDrownedIdleState()
	: qState((UINT)STATE_TYPE::DROWNEDIDLESTATE)
	, m_DetectRange(800.f)
	, m_AttackRange(400.f)
	, m_Bang(nullptr)
	, Bangflag(false)
{
}

qDrownedIdleState::~qDrownedIdleState()
{
}

void qDrownedIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(0, 10, true);

}

void qDrownedIdleState::FinalTick()
{
	Ptr<qMaterial> pBangMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(L"material\\bang.mtrl");

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qGameObject* Player = pCurLevel->FindObjectByName(L"Player");

	Vec3 DrownedPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 PlayerPos = Player->Transform()->GetRelativePos();
	
	Vec3 Dir = PlayerPos - DrownedPos;

	float Dist = Dir.Length();

	Bangflag = false;

	if (Dist < m_DetectRange && !Bangflag)
	{
		// 느낌표 생성
		m_Bang = new qGameObject;
		m_Bang->SetName(L"DrownedBang");

		m_Bang->AddComponent(new qMeshRender);
		m_Bang->MeshRender()->SetMesh(qAssetMgr::GetInst()->FindAsset<qMesh>(L"RectMesh"));
		m_Bang->MeshRender()->SetMaterial(pBangMtrl);

		m_Bang->AddComponent(new qTransform);
		m_Bang->Transform()->SetRelativeScale(25.f, 80.f, 1.f);

		pCurLevel->AddObject(12, m_Bang);

		Bangflag = true;
	}


	if (Dist < m_DetectRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qDrownedScript>()->GetDrownedDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"DrownedRun");
		}
		else
		{
			ChangeState(L"DrownedUturn");
		}
	}

	if (Dist < m_AttackRange)
	{
		DIRECTION CurDir = GetOwner()->GetScript<qDrownedScript>()->GetDrownedDir();

		// 같은 방향
		if (Dir.x * (int)CurDir > 0)
		{
			ChangeState(L"DrownedAttack");
		}
		else
		{
			ChangeState(L"DrownedUturn");
		}
	}
}

void qDrownedIdleState::Exit()
{
	Bangflag = false;
}
