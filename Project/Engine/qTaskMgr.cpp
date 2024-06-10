#include "pch.h"
#include "qTaskMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"


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
		}
		break;

		case TASK_TYPE::DELETE_OBJECT:
		{

		}
		break;

		case TASK_TYPE::CHANGE_LEVEL:
		{

		}
		break;
		}
	}

	m_vecTask.clear();	
}