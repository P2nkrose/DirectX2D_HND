#include "pch.h"
#include "SE_Detail.h"
#include "SE_AtlasView.h"

#include "qEditorMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qPathMgr.h>
#include <Engine/qAsset.h>
#include <Engine/qSprite.h>

SE_Detail::SE_Detail()
{
}

SE_Detail::~SE_Detail()
{
}

void SE_Detail::Init()
{
}

void SE_Detail::Update()
{
	ImGui::Text("");

	Atlas();

	ImGui::Text("");

	ImGui::Separator();

	ImGui::Text("");

	AtlasInfo();

	ImGui::Text("");

	ImGui::Separator();

	ImGui::Text("");

	SpriteInfo();

	ImGui::Text("");

	ImGui::Separator();

	ImGui::Text("");

	CreateSprite();
}

void SE_Detail::Atlas()
{
	string TexName;

	if (nullptr != m_AtlasTex)
		TexName = string(m_AtlasTex->GetKey().begin(), m_AtlasTex->GetKey().end());

	ImGui::Text("Atlas Texture Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##AtlasTex", (char*)TexName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
			if (ASSET_TYPE::TEXTURE == pAsset->GetAssetType())
			{
				SetAtlasTex((qTexture*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##AtlasTexBtn", ImVec2(30.f, 19.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&SE_Detail::SelectTexture);
		pListUI->SetActive(true);
	}
}

void SE_Detail::AtlasInfo()
{
	// ÇØ»óµµ
	UINT width = 0;
	UINT height = 0;

	if (nullptr != m_AtlasTex)
	{
		width = m_AtlasTex->Width();
		height = m_AtlasTex->Height();
	}

	char buff[50] = {};
	sprintf_s(buff, "%d", width);
	ImGui::Text("Width");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##TextureWidth", buff, 50, ImGuiInputTextFlags_ReadOnly);

	sprintf_s(buff, "%d", height);
	ImGui::Text("Height");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputText("##TextureHeight", buff, 50, ImGuiInputTextFlags_ReadOnly);

	// leftTop
	// slice
	// background
	// offset
	// Save     Load
}

void SE_Detail::SpriteInfo()
{
	// Left Top, Right Bottom
	//SE_AtlasView* AtalsView = (SE_AtlasView*)qEditorMgr::GetInst()->FindEditorUI("SE_AtlasView");
	//ImVec2 LeftTop = AtalsView->GetLeftTop();
	
	ImVec2 Offset = {};
	ImVec2 BackGround = {};

	if (nullptr != m_AtlasTex)
	{
		LeftTop = GetAtlasView()->GetLeftTop();
		RightBottom = GetAtlasView()->GetRightBottom();
	}

	ImGui::Text("Left Top");
	ImGui::SameLine(150);
	float LT[] = { LeftTop.x, LeftTop.y };
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputFloat2("##LT", LT);

	ImGui::Text("Slice");
	ImGui::SameLine(150);
	float Slice[] = { RightBottom.x - LeftTop.x, RightBottom.y - LeftTop.y };
	ImGui::SetNextItemWidth(200.f);
	ImGui::InputFloat2("##Slice", Slice);


}

void SE_Detail::CreateSprite()
{
	ImGui::Text("New Sprite Name");
	ImGui::SameLine(150);
	ImGui::SetNextItemWidth(200.f);

	char szName[255] = {};

	if (ImGui::InputText("##Sprite Name", szName, 255))
	{
		m_SpriteName = szName;
	}

	ImGui::SameLine();
	if (ImGui::Button("Create", ImVec2(50.f, 19.f)))
	{
		// wb
		Ptr<qSprite> pSprite = new qSprite;
		wstring strName = wstring(m_SpriteName.begin(), m_SpriteName.end());

		float Slice[] = { RightBottom.x - LeftTop.x, RightBottom.y - LeftTop.y };
		pSprite->Create(m_AtlasTex, Vec2(LeftTop.x, LeftTop.y), Vec2(Slice));
		pSprite->SetRelativePath(wstring(L"sprite\\") + strName + L".sprite");
		qAssetMgr::GetInst()->AddAsset(strName, pSprite);

		wstring ContentPath = qPathMgr::GetInst()->GetContentPath();

		pSprite->Save(ContentPath + L"sprite\\" + strName + L".sprite");

	}
}


void SE_Detail::SetAtlasTex(Ptr<qTexture> _Tex)
{
	m_AtlasTex = _Tex;
	GetAtlasView()->SetAtlasTex(m_AtlasTex);
}

void SE_Detail::SelectTexture(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
	{
		m_AtlasTex = nullptr;
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qTexture> pTex = qAssetMgr::GetInst()->FindAsset<qTexture>(strAssetName);

	assert(pTex.Get());

	SetAtlasTex(pTex);
}


