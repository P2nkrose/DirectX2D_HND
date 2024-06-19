#include "pch.h"
#include "qEditorMgr.h"

#include <Engine/components.h>
#include "qGameObjectEx.h"

#include <Engine/qKeyMgr.h>
#include <Engine/qRenderMgr.h>
#include "qEditorCameraScript.h"




qEditorMgr::qEditorMgr()
{

}

qEditorMgr::~qEditorMgr()
{
	Delete_Vec(m_vecEditorObject);
}

void qEditorMgr::Init()
{
	CreateEditorObject();
}

void qEditorMgr::Tick()
{
	for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
	{
		m_vecEditorObject[i]->Tick();
	}

	for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
	{
		m_vecEditorObject[i]->FinalTick();
	}
}

void qEditorMgr::CreateEditorObject()
{
	qGameObject* pEditorCamera = new qGameObjectEx;
	pEditorCamera->SetName(L"EditorCamera");
	pEditorCamera->AddComponent(new qTransform);
	pEditorCamera->AddComponent(new qCamera);
	pEditorCamera->AddComponent(new qEditorCameraScript);

	pEditorCamera->Camera()->SetLayerAll();
	pEditorCamera->Camera()->SetLayer(31, false);
	pEditorCamera->Camera()->SetFar(100000.f);
	pEditorCamera->Camera()->SetProjType(ORTHOGRAPHIC);

	m_vecEditorObject.push_back(pEditorCamera);

	qRenderMgr::GetInst()->RegisterEditorCamera(pEditorCamera->Camera());
}
