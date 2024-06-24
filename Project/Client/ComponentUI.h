#pragma once
#include "EditorUI.h"

class qGameObject;

class ComponentUI : public EditorUI
{
public:
	ComponentUI(COMPONENT_TYPE _Type);
	~ComponentUI();


public:
	void SetTargetObject(qGameObject* _Object);
	qGameObject* GetTargetObject() { return m_TargetObject; }


protected:
	void Title();


private:
	qGameObject*			m_TargetObject;
	const COMPONENT_TYPE	m_Type;
};

