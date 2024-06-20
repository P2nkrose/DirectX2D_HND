#include "pch.h"
#include "EditorUI.h"

// ���������� �ʱ�ȭ�� ���־�� �Ѵ�.
UINT EditorUI::m_GlobalID = 0;


EditorUI::EditorUI()
	: m_Active(true)
	, m_Parent(nullptr)
	, m_ID(m_GlobalID++)
{
}

EditorUI::~EditorUI()
{
	Delete_Vec(m_vecChildUI);
}

void EditorUI::Tick()
{
	if (!m_Active)
		return;

	// �ֻ��� �θ� UI �� ���
	if (nullptr == m_Parent)
	{
		ImGui::Begin(m_FullName.c_str(), &m_Active);

		Update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->Tick();
		}

		ImGui::End();
	}
	
	// �ڽ� Ÿ�� UI �� ���
	else
	{
		ImGui::BeginChild(m_FullName.c_str());

		Update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->Tick();
		}
		
		ImGui::EndChild();
	}
}

void EditorUI::AddChild(EditorUI* _UI)
{
	_UI->m_Parent = this;
	m_vecChildUI.push_back(_UI);
}

void EditorUI::SetName(const string& _Name)
{
	m_Name = _Name;

	// ID ���ڿ� ����
	m_FullName = m_Name;
	char szNum[50] = {};
	_itoa_s(m_ID, szNum, 10);
	m_FullName = m_FullName + "##" + szNum;
}
