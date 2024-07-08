#include "pch.h"
#include "qTaskMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"

#include "qAssetMgr.h"


qTaskMgr::qTaskMgr()
{}

qTaskMgr::~qTaskMgr()
{}

void qTaskMgr::Tick()
{
	ClearGC();

	ExecuteTask();
}

void qTaskMgr::ClearGC()
{
	Delete_Vec(m_GC);
}

void qTaskMgr::ExecuteTask()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		tTask& task = m_vecTask[i];
		switch (task.Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			int LayerIndex = task.Param_0;
			qGameObject* pObject = (qGameObject*)task.Param_1;
			pCurLevel->AddObject(LayerIndex, pObject);

			if (pCurLevel->GetState() != STOP)
			{
				pObject->Begin();
			}
		}
		break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			qGameObject* pObject = (qGameObject*)task.Param_0;
			if (pObject->m_Dead)
				continue;

			// GC¿¡ ³Ö±â
			pObject->m_Dead = true;
			m_GC.push_back(pObject);
		}
		break;

		case TASK_TYPE::CHANGE_LEVELSTATE:
		{
			LEVEL_STATE NextState = (LEVEL_STATE)task.Param_0;
			qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->ChangeState(NextState);
		}
		break;

		case TASK_TYPE::CHANGE_LEVEL:
		{

		}
		break;

		case TASK_TYPE::ASSET_CHANGED:
		{
			qAssetMgr::GetInst()->m_Changed = true;
		}
		break;
		}
	}

	m_vecTask.clear();	
}