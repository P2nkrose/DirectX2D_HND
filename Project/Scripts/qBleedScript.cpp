#include "pch.h"
#include "qBleedScript.h"

qBleedScript::qBleedScript()
	: qScript((UINT)SCRIPT_TYPE::BLEEDSCRIPT)
{
}

qBleedScript::~qBleedScript()
{
}

void qBleedScript::Begin()
{
}

void qBleedScript::Tick()
{
}

void qBleedScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qBleedScript::SaveToFile(FILE* _File)
{
}

void qBleedScript::LoadFromFile(FILE* _File)
{
}
