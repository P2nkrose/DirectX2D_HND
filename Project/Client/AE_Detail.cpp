#include "pch.h"
#include "AE_Detail.h"

#include "AE_Preview.h"
#include "AE_SpriteView.h"

#include "qEditorMgr.h"
#include "TreeUI.h"
#include "ListUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qPathMgr.h>
#include <Engine/qAsset.h>
#include <Engine/qSprite.h>
#include <Engine/qFlipBook.h>
#include <Engine/qFlipBookComponent.h>

#include <Engine/qGameObject.h>

AE_Detail::AE_Detail()
{
}

AE_Detail::~AE_Detail()
{
}

void AE_Detail::Init()
{
}

void AE_Detail::Update()
{
	Animation();

	ImGui::Text("");

	ImGui::Separator();

	ImGui::Text("");

	AnimInfo();

	SpriteList();

	AddAnimation();

	DeleteAnimation();
}


void AE_Detail::Animation()
{
	ImGui::Text("");

	string AnimName;

	if (nullptr != m_CurFlipBook)
		AnimName = string(m_CurFlipBook->GetKey().begin(), m_CurFlipBook->GetKey().end());

	ImGui::Text("");
	ImGui::SameLine();
	ImGui::Text("Animation Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##AnimName", (char*)AnimName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
			if (ASSET_TYPE::FLIPBOOK == pAsset->GetAssetType())
			{
				SetAnim((qFlipBook*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();

	if (ImGui::Button("##AnimListBtn", ImVec2(30.f, 19.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("AnimList");
		pListUI->ShowNameOnly(true);
		vector<string> vecAnimNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::FLIPBOOK, vecAnimNames);
		pListUI->AddList(vecAnimNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&AE_Detail::SelectAnim);
		pListUI->SetActive(true);
	}


}

void AE_Detail::AnimInfo()
{
	if (nullptr == m_CurFlipBook)
		return;

	ImGui::Text("");
	ImGui::SameLine();
	ImGui::Text("Frame Size");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200);
	m_MaxFrm = m_CurFlipBook->GetMaxFrameCount();
	ImGui::DragInt("##FrameSize", &m_MaxFrm, 0.1f);

	//ImGui::DragInt("##FrameIdx", &m_CurFrmIdx, 0.1f);
	
	


}

void AE_Detail::SpriteList()
{

	//m_CurFrmSprite = m_CurFlipBook->GetSprite(m_CurFrmIdx);
	//
	//
	//for (size_t i = 0; i < m_MaxFrm; ++i)
	//{
	//	m_vecSprite.push_back(m_CurFrmSprite);
	//}
	//
	//
	//
	//const char* sprites[] = m_CurFlipBook->GetName();
	//
	//m_CurFrmIdx;
	//
	//const char* list_preview_value = sprites[(UINT)Type];
	//
	//
	//m_MaxFrm;
	//
	//ImGui::BeginListBox;
}

void AE_Detail::AddAnimation()
{
}

void AE_Detail::DeleteAnimation()
{
}


void AE_Detail::SetAnim(Ptr<qFlipBook> _FlipBook)
{
	m_CurFlipBook = _FlipBook;
	GetPreview()->SetAnim(_FlipBook);
}


void AE_Detail::SelectAnim(DWORD_PTR _ListUI)
{
	m_List = (ListUI*)_ListUI;
	string strName = m_List->GetSelectName();

	if (strName == "None")
	{
		m_CurFlipBook = nullptr;
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qFlipBook> pAnim = qAssetMgr::GetInst()->FindAsset<qFlipBook>(strAssetName);

	assert(pAnim.Get());

	SetAnim(pAnim);
}
