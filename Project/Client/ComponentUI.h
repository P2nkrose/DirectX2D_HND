#pragma once
#include "EditorUI.h"

class qGameObject;

class ComponentUI : public EditorUI
{
public:
	ComponentUI();
	~ComponentUI();


public:
	void SetTargetObject(qGameObject* _Object) { m_TargetObject = _Object; }
	qGameObject* GetTargetObject() { return m_TargetObject; }



private:
	qGameObject* m_TargetObject;
};

