#pragma once
#include "EditorUI.h"


class TreeNode
{
public:
	friend class TreeUI;

	TreeNode(UINT _ID);
	~TreeNode();


public:
	void Update();

public:
	void SetName(const string& _Name) { m_Name = _Name; }
	const string& GetName() { return m_Name; }

	void SetFrame(bool _Frame) { m_Frame = _Frame; }
	bool IsFrame() { return m_Frame; }

	DWORD_PTR GetData() { return m_Data; }

	void AddChildNode(TreeNode* _Node) { m_vecChildNode.push_back(_Node); }

public:
	void DragCheck();
	void DropCheck();


private:
	class TreeUI*			m_Owner;			// ��尡 �ڽ��� �����ִ� ���� �˰� �Ѵ�.

	string					m_Name;
	TreeNode*				m_ParentNode;
	vector<TreeNode*>		m_vecChildNode;
	const UINT				m_ID;
	DWORD_PTR				m_Data;

	bool					m_Frame;
	bool					m_Selected;
};




class TreeUI : public EditorUI
{
public:
	TreeUI();
	~TreeUI();

public:
	virtual void Update() override;

public:
	TreeNode* AddNode(TreeNode* _Parent, const string& _Name, DWORD_PTR _Data = 0);
	void ShowRoot(bool _Show) { m_ShowRoot = _Show; }
	bool IsShowRoot() { return m_ShowRoot; }

	

	void SetSelectedNode(TreeNode* _Node);
	void SetDragedNode(TreeNode* _Node);
	void SetDroppedNode(TreeNode* _Node);

	void UseDrag(bool _Drag) { m_UseDrag = _Drag; }
	void UseDrop(bool _Drop) { m_UseDrop = _Drop; }

	bool IsDrag() { return m_UseDrag; }
	bool IsDrop() { return m_UseDrop; }

	void SetDropPayLoadName(const string& _Name) { m_DropPayLoadName = _Name; }
	const string GetDropPayLoadName() { return m_DropPayLoadName; }

	void AddClickedDelegate(EditorUI* _Inst, DELEGATE_1 _Func) { m_ClickedInst = _Inst; m_ClickedFunc = _Func; }
	void AddDragDropDelegate(EditorUI* _Inst, DELEGATE_2 _Func) { m_SelfDragDropInst = _Inst; m_SelfDragDropFunc = _Func; }
	void AddDropDelegate(EditorUI* _Inst, DELEGATE_2 _Func) { m_DropInst = _Inst; m_DropFunc = _Func; }

	void Clear();

private:
	TreeNode*		m_Root;
	TreeNode*		m_SelectedNode;
	TreeNode*		m_DragedNode;		// �巡�׵� ���
	TreeNode*		m_DroppedNode;		// ����� ���

	UINT			m_NodeID;
	bool			m_ShowRoot;
	bool			m_UseDrag;
	bool			m_UseDrop;



	EditorUI*		m_ClickedInst;
	DELEGATE_1		m_ClickedFunc;

	EditorUI*		m_SelfDragDropInst;
	DELEGATE_2		m_SelfDragDropFunc;

	EditorUI*		m_DropInst;
	DELEGATE_2		m_DropFunc;
	string			m_DropPayLoadName;


};
