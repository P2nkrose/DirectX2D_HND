#include "pch.h"
#include "ScriptUI.h"

#include <Scripts/qScriptMgr.h>
#include <Engine/qScript.h>

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
	m_UIHeight = 0;

	ImGui::PushID((int)GetComponentUIType());
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));

	wstring strScriptName = qScriptMgr::GetScriptName(m_Script);
	ImGui::Button(string(strScriptName.begin(), strScriptName.end()).c_str());

	ImGui::PopStyleColor(3);
	ImGui::PopID();

	m_UIHeight += (int)ImGui::GetItemRectSize().y;

	// Script 에서 노출시킬 데이터를 보여준다.
	const vector<tScriptParam>& vecParam = m_Script->GetScriptParam();

	for (size_t i = 0; i < vecParam.size(); ++i)
	{
		switch (vecParam[i].Type)
		{
		case SCRIPT_PARAM::INT:
			ParamUI::InputInt((int*)vecParam[i].pData, vecParam[i].Desc);
			break;
		case SCRIPT_PARAM::FLOAT:
			ParamUI::InputFloat((float*)vecParam[i].pData, vecParam[i].Desc);
			break;
		case SCRIPT_PARAM::VEC2:
			ParamUI::InputFloat((float*)vecParam[i].pData, vecParam[i].Desc);
			break;
		case SCRIPT_PARAM::VEC3:

			break;
		case SCRIPT_PARAM::VEC4:
			ParamUI::InputVec4((Vec4*)vecParam[i].pData, vecParam[i].Desc);
			break;
		case SCRIPT_PARAM::TEXTURE:
		{
			Ptr<qTexture>& pTex = *((Ptr<qTexture>*)vecParam[i].pData);
			ParamUI::InputTexture(pTex, vecParam[i].Desc);
			m_UIHeight += 8;
		}
		break;
		}

		m_UIHeight += (int)ImGui::GetItemRectSize().y;
	}

	SetChildSize(ImVec2(0.f, (float)m_UIHeight));

}

void ScriptUI::SetTargetScript(qScript* _Script)
{
	m_Script = _Script;

	if (nullptr != m_Script)
		SetActive(true);
	else
		SetActive(false);
}
