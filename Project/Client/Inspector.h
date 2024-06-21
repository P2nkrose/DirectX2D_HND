#pragma once
#include "EditorUI.h"

class qGameObject;

class Inspector : public EditorUI
{
public:
	Inspector();
	~Inspector();

public:
	virtual void Update() override;

public:
	void SetTargetObject(qGameObject* _Object) { m_TargetObject = _Object; }


private:
	qGameObject*		m_TargetObject;

};

