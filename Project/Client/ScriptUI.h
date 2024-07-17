#pragma once
#include "ComponentUI.h"

#include <Scripts/qScriptMgr.h>
#include <Engine/qScript.h>

#include "ParamUI.h"

class ScriptUI : public ComponentUI
{
public:
	ScriptUI();
	~ScriptUI();

public:
	virtual void Update() override;

public:
	void SetTargetScript(qScript* _Script);
	qScript* GetTargetScript() { return m_Script; }


private:
	class qScript*			m_Script;
	uintptr_t				m_UIHeight;
};

