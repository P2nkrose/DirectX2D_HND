#pragma once
#include "EditorUI.h"


class TreeNode
{
public:
	TreeNode();
	~TreeNode();


public:
	void Update();

public:
	void SetName(const string& _Name) { m_Name = _Name; }
	const string& GetName() { return m_Name; }

	void AddChildNode(TreeNode* _Node) { m_vecChildNode.push_back(_Node); }


private:
	string					m_Name;
	TreeNode*				m_ParentNode;
	vector<TreeNode*>		m_vecChildNode;

};




class TreeUI : public EditorUI
{
public:
	TreeUI();
	~TreeUI();

public:
	virtual void Update() override;

public:
	void AddNode(const string& _Name);


private:
	TreeNode*		m_Root;
};

