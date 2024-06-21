#include "pch.h"
#include "Inspector.h"

#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>


Inspector::Inspector()
	: m_TargetObject(nullptr)
{
}

Inspector::~Inspector()
{
}

void Inspector::Update()
{
	if (nullptr == m_TargetObject)
	{
		m_TargetObject = qLevelMgr::GetInst()->FindObjectByName(L"Player");
		return;
	}

	// ==================
	//    Object Name
	// ==================

	string strObjectName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
	ImGui::Text("Object Name");
	ImGui::SameLine(100);
	ImGui::InputText("##ObjectName", (char*)strObjectName.c_str(), strObjectName.length(), ImGuiInputTextFlags_ReadOnly);

	// ============
	//    Layer
	// ============

	int LayerIdx = m_TargetObject->GetLayerIdx();
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	qLayer* pLayer = pCurLevel->GetLayer(LayerIdx);
	string LayerName = string(pLayer->GetName().begin(), pLayer->GetName().end());

	char buffer[50] = {};

	if (LayerName.empty())
		sprintf_s(buffer, 50, "%d : %s", LayerIdx, "None");
	else
		sprintf_s(buffer, 50, "%d : %s", LayerIdx, LayerName.c_str());

	ImGui::Text("Layer");
	ImGui::SameLine(100);
	ImGui::InputText("##LayerName", buffer, strlen(buffer), ImGuiInputTextFlags_ReadOnly);

}
