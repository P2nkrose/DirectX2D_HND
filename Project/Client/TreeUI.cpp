#include "pch.h"
#include "TreeUI.h"


// ========
// TreeNode
// ========

TreeNode::TreeNode(UINT _ID)
	: m_Owner(nullptr)
	, m_ParentNode(nullptr)
	, m_ID(_ID)
	, m_Data(0)
	, m_Frame(false)
	, m_Selected(false)
{
}

TreeNode::~TreeNode()
{
	Delete_Vec(m_vecChildNode);
}

void TreeNode::Update()
{
	UINT Flag = ImGuiTreeNodeFlags_OpenOnArrow
			  | ImGuiTreeNodeFlags_SpanAvailWidth
			  | ImGuiTreeNodeFlags_OpenOnDoubleClick;

	if(m_Frame)
		Flag |= ImGuiTreeNodeFlags_Framed;

	if (m_Selected)
		Flag |= ImGuiTreeNodeFlags_Selected;

	char Name[255] = {};

	if (m_vecChildNode.empty())
	{
		Flag |= ImGuiTreeNodeFlags_Leaf;
		
		if(m_Frame)
			sprintf_s(Name, 255, "   %s##%d", m_Name.c_str(), m_ID);
		else
			sprintf_s(Name, 255, "%s##%d", m_Name.c_str(), m_ID);
	}
	else
	{
		sprintf_s(Name, 255, "%s##%d", m_Name.c_str(), m_ID);
	}


	if (ImGui::TreeNodeEx(Name, Flag))
	{
		// 클릭 체크
		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		{
			m_Owner->SetSelectedNode(this);
		}

		// Drag 체크
		DragCheck();

		// Drop 체크
		DropCheck();


		for (size_t i = 0; i < m_vecChildNode.size(); ++i)
		{
			m_vecChildNode[i]->Update();
		}
		
		ImGui::TreePop();
	}
}

void TreeNode::DragCheck()
{
	// 1. 사용자가 Drag를 시작할때 BeginDragDropSource 함수가 실시됨
	// 2. 옮길 데이터(PayLoad) 설정하기
	// 3. Drag 된 Node 의 이름을 마우스 옆 text로 띄워주기
	if (m_Owner->IsDrag())
	{
		if (ImGui::BeginDragDropSource())
		{
			TreeNode* pThis = this;

			ImGui::SetDragDropPayload(m_Owner->GetName().c_str(), &pThis, sizeof(TreeNode*));
			ImGui::Text(m_Name.c_str());
			ImGui::EndDragDropSource();

			m_Owner->SetDragedNode(this);
		}
	}
}

void TreeNode::DropCheck()
{
	if (!m_Owner->IsDrop())
		return;

	if (ImGui::BeginDragDropTarget())
	{
		// 내용 넣기



		m_Owner->SetDroppedNode(this);

		ImGui::EndDragDropTarget();
	}

}




// ======
// TreeUI
// ======

TreeUI::TreeUI()
	: m_Root(nullptr)
	, m_SelectedNode(nullptr)
	, m_DragedNode(nullptr)
	, m_DroppedNode(nullptr)
	, m_NodeID(0)
	, m_ShowRoot(false)
	, m_UseDrag(false)
	, m_UseDrop(false)
	, m_ClickedInst(nullptr)
	, m_ClickedFunc(nullptr)
{
}

TreeUI::~TreeUI()
{
	Clear();
}

void TreeUI::Update()
{
	if (nullptr == m_Root)
		return;

	if(m_ShowRoot)
		m_Root->Update();
	else
	{
		for (size_t i = 0; i < m_Root->m_vecChildNode.size(); ++i)
		{
			m_Root->m_vecChildNode[i]->Update();
		}
	}

	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
	{
		m_DroppedNode = m_DragedNode = nullptr;
	}
}


TreeNode* TreeUI::AddNode(TreeNode* _Parent, const string& _Name, DWORD_PTR _Data)
{
	// 노드 생성 및 이름, ID 세팅
	TreeNode* pNode = new TreeNode(m_NodeID++);
	pNode->m_Owner = this;
	pNode->SetName(_Name);
	pNode->m_Data = _Data;
	
	// 부모가 지정되지 않으면 노드를 루트로 지정한다.
	if (nullptr == _Parent)
	{
		assert(!m_Root);

		m_Root = pNode;
	}
	else
	{
		_Parent->AddChildNode(pNode);
	}

	return pNode;
}


void TreeUI::SetSelectedNode(TreeNode* _Node)
{
	// 기존에 선택상태였던 노드를 선택상태 해제하고
	if (nullptr != m_SelectedNode)
		m_SelectedNode->m_Selected = false;

	// 새로운 노드를 선택된 노드로 갱신
	m_SelectedNode = _Node;

	// 새로운 노드를 선택된 상태로 만들어줌
	if (nullptr != m_SelectedNode)
	{
		m_SelectedNode->m_Selected = true;

		if (m_ClickedInst && m_ClickedFunc)
		{
			(m_ClickedInst->*m_ClickedFunc)((DWORD_PTR)m_SelectedNode);
		}
	}
}

void TreeUI::SetDragedNode(TreeNode* _Node)
{
	m_DragedNode = _Node;
}

void TreeUI::SetDroppedNode(TreeNode* _Node)
{
	// Drag 된 노드가 없는 경우 (외부 데이터가 트리로 드랍된 경우)
	if (nullptr == m_DragedNode)
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(m_DropPayLoadName.c_str());
		if (payload)
		{
			m_DroppedNode = _Node;

			if (m_DropInst && m_DropFunc)
				(m_DropInst->*m_DropFunc)((DWORD_PTR)payload->Data, (DWORD_PTR)m_DroppedNode);
		}
	}

	// Self Drag Drop 된 상황
	else
	{
		assert(m_DragedNode->m_Owner == this);

		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(GetName().c_str());
		if (payload)
		{
			m_DroppedNode = _Node;

			if (m_SelfDragDropInst && m_SelfDragDropFunc)
				(m_SelfDragDropInst->*m_SelfDragDropFunc)((DWORD_PTR)m_DragedNode, (DWORD_PTR)m_DroppedNode);
		}
	}


	m_DroppedNode = _Node;
}

void TreeUI::Clear()
{
	if (nullptr != m_Root)
	{
		delete m_Root;
		m_Root = nullptr;
	}
}
