#include "pch.h"
#include "Outliner.h"

#include "TreeUI.h"
#include "Inspector.h"
#include "qEditorMgr.h"

#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>

Outliner::Outliner()
{
	m_Tree = new TreeUI;
	m_Tree->SetName("OutlinerTree");
	AddChild(m_Tree);

	// 트리 옵션 세팅
	m_Tree->ShowRoot(false);	// 루트 보이지 않기
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Outliner::GameObjectClicked);

	// Asset 상태를 Content 의 TreeUI 에 반영
	RenewLevel();
}

Outliner::~Outliner()
{
}

void Outliner::Update()
{
}

void Outliner::RenewLevel()
{
	// 모든 내용 삭제
	m_Tree->Clear();

	// 루트 노드 생성
	TreeNode* pRootNode = m_Tree->AddNode(nullptr, "Root", 0);

	qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pLevel)
		return;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = pLevel->GetLayer(i);
		const vector<qGameObject*>& vecObjects = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecObjects.size(); ++i)
		{
			AddGameObject(pRootNode, vecObjects[i]);
		}
	}
}

void Outliner::AddGameObject(TreeNode* pNode, qGameObject* _Object)
{
	string ObjectName = string(_Object->GetName().begin(), _Object->GetName().end());

	TreeNode* pObjectNode = m_Tree->AddNode(pNode, ObjectName.c_str(), (DWORD_PTR)_Object);

	const vector<qGameObject*>& vecChild = _Object->GetChildren();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddGameObject(pObjectNode, vecChild[i]);
	}
}


void Outliner::GameObjectClicked(DWORD_PTR _Param)
{
	TreeNode* pNode = (TreeNode*)_Param;

	qGameObject* pObject = (qGameObject*)pNode->GetData();

	Inspector* pInspector = (Inspector*)qEditorMgr::GetInst()->FindEditorUI("Inspector");
	pInspector->SetTargetObject(pObject);
	ImGui::SetWindowFocus(nullptr);
}


