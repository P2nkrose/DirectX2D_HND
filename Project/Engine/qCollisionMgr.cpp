#include "pch.h"
#include "qCollisionMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"
#include "qCollider2D.h"



qCollisionMgr::qCollisionMgr()
	: m_Matrix{}
{

}


qCollisionMgr::~qCollisionMgr()
{

}

void qCollisionMgr::Tick()
{
	for (int Row = 0; Row < MAX_LAYER; ++Row)
	{
		for (int Col = Row; Col < MAX_LAYER; ++Col)
		{
			if (m_Matrix[Row] & (1 << Col))
			{
				CollisionBtwLayer(Row, Col);
			}
		}
	}
}

void qCollisionMgr::CollisionCheck(UINT Layer1, UINT Layer2)
{
	UINT Row = Layer1;
	UINT Col = Layer2;

	if (Row > Col)
	{
		Row = (UINT)Layer2;
		Col = (UINT)Layer1;
	}

	if (m_Matrix[Row] & (1 << Col))
	{
		m_Matrix[Row] &= ~(1 << Col);
	}
	else
	{
		m_Matrix[Row] |= (1 << Col);
	}
}

void qCollisionMgr::CollisionBtwLayer(UINT _Left, UINT _Right)
{
	// ���� ������ �����´�.
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	// �� ���̾ ���� ��� ������Ʈ���� �����´�.
	const vector<qGameObject*>& vecLeft = pCurLevel->GetLayer(_Left)->GetObjects();
	const vector<qGameObject*>& vecRight = pCurLevel->GetLayer(_Right)->GetObjects();

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		qCollider2D* pLeftCol = vecLeft[i]->Collider2D();
		if (nullptr == pLeftCol)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			qCollider2D* pRightCol = vecRight[j]->Collider2D();
			if (nullptr == pRightCol)
				continue;

			COLLIDER_ID id = {};

			id.LeftID = pLeftCol->GetID();
			id.RightID = pRightCol->GetID();

			map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(id.ID);

			// ��ϵ����� ������ ��Ͻ�Ų��.
			if (iter == m_mapCollisionInfo.end())
			{
				m_mapCollisionInfo.insert(make_pair(id.ID, false));
				iter = m_mapCollisionInfo.find(id.ID);
			}

			//bool bDead = vecLeft[i]->GetOwner()->IsDead() || vecRight[j]->GetOwner()->IsDead();
			//bool bDeactive = !vecLeft[i]->IsActive() || !vecRight[j]->IsActive();

			// �� �浹ü�� ���� �浹���̴�.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// �������� �浹���̾���.
				if (iter->second)
				{
					pLeftCol->Overlap(pRightCol);
					pRightCol->Overlap(pLeftCol);
				}

				// �������� �浹���� �ƴϾ���.
				else
				{
					pLeftCol->BeginOverlap(pRightCol);
					pRightCol->BeginOverlap(pLeftCol);
				}

				iter->second = true;

				// �� �浹ü�� �ϳ��� Dead ���°ų� ��Ȱ��ȭ ���¶��
				// �߰��� �浹 ������ ȣ������ش�.
				/*if (bDead || bDeactive)
				{
					vecLeft[i]->EndOverlap(vecRight[j]);
					vecRight[j]->EndOverlap(vecLeft[i]);
					iter->second = false;
				}*/
			}

			// �� �浹ü�� ���� �浹���� �ƴϴ�.
			else
			{
				// �������� �浹���̾���.
				if (iter->second)
				{
					pLeftCol->EndOverlap(pRightCol);
					pRightCol->EndOverlap(pLeftCol);
				}

				iter->second = false;
			}
		}
	}
}

bool qCollisionMgr::IsCollision(qCollider2D* _Left, qCollider2D* _Right)
{
	return false;
}
