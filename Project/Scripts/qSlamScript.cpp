#include "pch.h"
#include "qSlamScript.h"

qSlamScript::qSlamScript()
	: qScript((UINT)SCRIPT_TYPE::SLAMSCRIPT)
{
}

qSlamScript::~qSlamScript()
{
}

void qSlamScript::Begin()
{
}

void qSlamScript::Tick()
{
}

void qSlamScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qSlamScript::SaveToFile(FILE* _File)
{
}

void qSlamScript::LoadFromFile(FILE* _File)
{
}
