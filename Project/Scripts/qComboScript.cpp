#include "pch.h"
#include "qComboScript.h"

#include <Engine/qGameObject.h>
#include <Engine/qLevelMgr.h>

#include <Engine/qScript.h>
#include "qPlayerScript.h"


qComboScript::qComboScript()
	: qScript(UINT(SCRIPT_TYPE::COMBOSCRIPT))
{
}

qComboScript::~qComboScript()
{
}

void qComboScript::Begin()
{
}

void qComboScript::Tick()
{
}

void qComboScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qComboScript::SaveToFile(FILE* _File)
{
}

void qComboScript::LoadFromFile(FILE* _File)
{
}
