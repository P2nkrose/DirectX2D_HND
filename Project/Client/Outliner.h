#pragma once
#include "EditorUI.h"

class TreeNode;
class qGameObject;

class Outliner : public EditorUI
{
public:
	Outliner();
	~Outliner();

public:
	virtual void Update() override;

private:
	void RenewLevel();
	void GameObjectClicked(DWORD_PTR _Param);
	void AddGameObject(TreeNode* pNode, qGameObject* _Object);

private:
	class TreeUI*		m_Tree;

};

