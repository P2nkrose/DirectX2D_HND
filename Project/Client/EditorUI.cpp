#include "pch.h"
#include "EditorUI.h"

EditorUI::EditorUI()
	: m_Active(true)
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Tick()
{
	if (!m_Active)
		return;

	ImGui::Begin(m_Name.c_str(), &m_Active);

	Update();

	ImGui::End();
}
