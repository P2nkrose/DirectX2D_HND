#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/qMeshRender.h>
#include <Engine/qMesh.h>
#include <Engine/qMaterial.h>

#include "qEditorMgr.h"
#include "ListUI.h"

MeshRenderUI::MeshRenderUI()
	: ComponentUI(COMPONENT_TYPE::MESHRENDER)
{
}

MeshRenderUI::~MeshRenderUI()
{
}



void MeshRenderUI::Update()
{
	Title();

	qMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	// 메쉬 정보
	Ptr<qMesh> pMesh = pMeshRender->GetMesh();

	string MeshName = string(pMesh->GetKey().begin(), pMesh->GetKey().end());
	ImGui::Text("Mesh");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##MeshKey", (char*)MeshName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("##MeshBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Mesh");
		vector<string> vecMeshNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::MESH, vecMeshNames);
		pListUI->AddList(vecMeshNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMesh);
		pListUI->SetActive(true);
	}


	// 머티리얼 정보
	Ptr<qMaterial> pMtrl = pMeshRender->GetMaterial();

	string MtrlName = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());
	ImGui::Text("Material");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##MaterialKey", (char*)MtrlName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	ImGui::SameLine();
	if (ImGui::Button("##MtrlBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("Material");
		vector<string> vecMtrlNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::MATERIAL, vecMtrlNames);
		pListUI->AddList(vecMtrlNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMaterial);
		pListUI->SetActive(true);
	}
}


void MeshRenderUI::SelectMesh(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qMesh> pMesh = qAssetMgr::GetInst()->FindAsset<qMesh>(strAssetName);

	assert(pMesh.Get());

	qMeshRender* pMeshRender = GetTargetObject()->MeshRender();
	pMeshRender->SetMesh(pMesh);
}

void MeshRenderUI::SelectMaterial(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qMaterial> pMtrl = qAssetMgr::GetInst()->FindAsset<qMaterial>(strAssetName);

	assert(pMtrl.Get());

	qMeshRender* pMeshRender = GetTargetObject()->MeshRender();
	pMeshRender->SetMaterial(pMtrl);
}