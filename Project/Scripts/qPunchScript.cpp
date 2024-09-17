#include "pch.h"
#include "qPunchScript.h"

qPunchScript::qPunchScript()
	: qScript((UINT)SCRIPT_TYPE::PUNCHSCRIPT)
{
}

qPunchScript::~qPunchScript()
{
}

void qPunchScript::Begin()
{
}

void qPunchScript::Tick()
{
}

void qPunchScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qPunchScript::SaveToFile(FILE* _File)
{
}

void qPunchScript::LoadFromFile(FILE* _File)
{
}
