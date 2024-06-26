#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/qMeshRender.h>
#include <Engine/qMesh.h>
#include <Engine/qMaterial.h>

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
	ImGui::InputText("##MeshKey", (char*)MeshName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);


	// 머티리얼 정보
	Ptr<qMaterial> pMtrl = pMeshRender->GetMaterial();

	string MtrlName = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());
	ImGui::Text("Material");
	ImGui::SameLine(100);
	ImGui::InputText("##MaterialKey", (char*)MtrlName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
}
