#include "pch.h"
#include "qScript.h"

qScript::qScript(UINT _ScriptType)
	: qComponent(COMPONENT_TYPE::SCRIPT)
	, m_ScriptType(_ScriptType)
{
}

qScript::~qScript()
{
}
