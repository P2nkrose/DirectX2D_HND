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

private:
	class TreeUI*			m_Owner;			// 노드가 자신이 속해있는 탭을 알게 한다.

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
	void AddClickedDelegate(EditorUI* _Inst, DELEGATE_1 _Func) { m_ClickedInst = _Inst; m_ClickedFunc = _Func; }


private:
	TreeNode*		m_Root;
	TreeNode*		m_SelectedNode;

	UINT			m_NodeID;
	bool			m_ShowRoot;

	EditorUI*		m_ClickedInst;
	DELEGATE_1		m_ClickedFunc;
};

