#include "pch.h"
#include "qCrashScript.h"

qCrashScript::qCrashScript()
	: qScript((UINT)SCRIPT_TYPE::CRASHSCRIPT)
{
}

qCrashScript::~qCrashScript()
{
}

void qCrashScript::Begin()
{
}

void qCrashScript::Tick()
{
}

void qCrashScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qCrashScript::SaveToFile(FILE* _File)
{
}

void qCrashScript::LoadFromFile(FILE* _File)
{
}
