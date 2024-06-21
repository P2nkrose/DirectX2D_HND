#pragma once
#include "EditorUI.h"

class qGameObject;
class ComponentUI;

class Inspector : public EditorUI
{
public:
	Inspector();
	~Inspector();

public:
	virtual void Update() override;

public:
	void SetTargetObject(qGameObject* _Object);


private:
	qGameObject*		m_TargetObject;
	ComponentUI*		m_arrComUI[(UINT)COMPONENT_TYPE::END];
};

