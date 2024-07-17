#include "pch.h"
#include "ScriptUI.h"

ScriptUI::ScriptUI()
	: ComponentUI(COMPONENT_TYPE::SCRIPT)
	, m_Script(nullptr)
	, m_UIHeight(0)
{
}

ScriptUI::~ScriptUI()
{
}

void ScriptUI::Update()
{
	ImGui::PushID((int)GetComponentUIType());
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));

	wstring strScriptName = qScriptMgr::GetScriptName(m_Script);
	ImGui::Button(string(strScriptName.begin(), strScriptName.end()).c_str());

	ImGui::PopStyleColor(3);
	ImGui::PopID();

	ImVec2 vWinSize = ImGui::GetItemRectSize();
	SetChildSize(ImVec2(0.f, vWinSize.y));

}

void ScriptUI::SetTargetScript(qScript* _Script)
{
	m_Script = _Script;

	if (nullptr != m_Script)
		SetActive(true);
	else
		SetActive(false);
}
