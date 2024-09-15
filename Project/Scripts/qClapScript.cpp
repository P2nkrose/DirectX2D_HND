#include "pch.h"
#include "qClapScript.h"

qClapScript::qClapScript()
	: qScript((UINT)SCRIPT_TYPE::CLAPSCRIPT)
{
}

qClapScript::~qClapScript()
{
}

void qClapScript::Begin()
{
}

void qClapScript::Tick()
{
}

void qClapScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qClapScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qClapScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qClapScript::SaveToFile(FILE* _File)
{
}

void qClapScript::LoadFromFile(FILE* _File)
{
}
