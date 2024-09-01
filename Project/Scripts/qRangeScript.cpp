#include "pch.h"
#include "qRangeScript.h"

qRangeScript::qRangeScript()
	: qScript((UINT)SCRIPT_TYPE::RANGESCRIPT)
{
}

qRangeScript::~qRangeScript()
{
}

void qRangeScript::Begin()
{
}

void qRangeScript::Tick()
{
}

void qRangeScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qRangeScript::SaveToFile(FILE* _File)
{
}

void qRangeScript::LoadFromFile(FILE* _File)
{
}
