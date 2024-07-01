#pragma once
#include "EditorUI.h"

class Content : public EditorUI
{
public:
	Content();
	~Content();

public:
	virtual void Update() override;

private:
	class TreeUI*		m_Tree;
};

