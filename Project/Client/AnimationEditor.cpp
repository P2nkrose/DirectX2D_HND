#include "pch.h"
#include "AnimationEditor.h"

#include "qEditorMgr.h"

#include "AE_Detail.h"
#include "AE_Preview.h"
#include "AE_SpriteView.h"

AnimationEditor::AnimationEditor()
{
}

AnimationEditor::~AnimationEditor()
{
}

void AnimationEditor::Init()
{
	m_Preview = (AE_Preview*)qEditorMgr::GetInst()->FindEditorUI("AE_Preview");
	m_SpriteView = (AE_SpriteView*)qEditorMgr::GetInst()->FindEditorUI("AE_SpriteView");
	m_Detail = (AE_Detail*)qEditorMgr::GetInst()->FindEditorUI("AE_Detail");

	m_Preview->SetMove(false);
	m_SpriteView->SetMove(false);
	m_Detail->SetMove(false);

	m_Preview->m_Owner = this;
	m_SpriteView->m_Owner = this;
	m_Detail->m_Owner = this;

}

void AnimationEditor::Update()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Window"))
		{
			bool Preview = m_Preview->IsActive();
			bool Detail = m_Detail->IsActive();
			bool SpriteView = m_SpriteView->IsActive();

			if (ImGui::MenuItem("Preview", nullptr, &Preview))
			{
				m_Preview->SetActive(Preview);
			}

			if (ImGui::MenuItem("SpriteView", nullptr, &SpriteView))
			{
				m_SpriteView->SetActive(SpriteView);
			}

			if (ImGui::MenuItem("Detail", nullptr, &Detail))
			{
				m_Detail->SetActive(Detail);
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void AnimationEditor::Activate()
{
	//m_AtlasView->SetActive(true);
	//m_Detail->SetActive(true);
}

void AnimationEditor::Deactivate()
{
}

void AnimationEditor::AddAnimation()
{
}

void AnimationEditor::DeleteAnimation(const wstring& _strAnimationName)
{
}
