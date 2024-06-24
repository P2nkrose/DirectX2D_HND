#include "pch.h"
#include "ComponentUI.h"

#include <Engine/qGameObject.h>
#include <Engine/qComponent.h>

ComponentUI::ComponentUI(COMPONENT_TYPE _Type)
	: m_TargetObject(nullptr)
	, m_Type(_Type)
{

}

ComponentUI::~ComponentUI()
{
}

void ComponentUI::SetTargetObject(qGameObject* _Object)
{
	m_TargetObject = _Object;

	if (nullptr != m_TargetObject && nullptr != m_TargetObject->GetComponent(m_Type))
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

void ComponentUI::Title()
{
	ImGui::PushID((int)m_Type);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));

	ImGui::Button(ToString(m_Type));

	ImGui::PopStyleColor(3);
	ImGui::PopID();
}