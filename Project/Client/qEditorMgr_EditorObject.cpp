#include "pch.h"

#include "qEditorMgr.h"
#include "qGameObjectEx.h"
#include <Engine/components.h>

#include "qEditorCameraScript.h"
#include <Engine/qRenderMgr.h>




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