#include "pch.h"
#include "Content.h"

#include "TreeUI.h"

Content::Content()
{
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChild(m_Tree);

	m_Tree->AddNode("Parent");
}

Content::~Content()
{
}

void Content::Update()
{
	// Separator : ���м�
	//ImGui::Separator();

	// Asset Manager ���� ���� Asset ������ ��� �ش�.

}
