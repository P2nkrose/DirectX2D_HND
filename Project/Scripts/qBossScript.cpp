#include "pch.h"
#include "qBossScript.h"

qBossScript::qBossScript()
	: qScript((UINT)SCRIPT_TYPE::BOSSSCRIPT)
{
}

qBossScript::~qBossScript()
{
}

void qBossScript::Begin()
{
}

void qBossScript::Tick()
{
}

void qBossScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qBossScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qBossScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qBossScript::SaveToFile(FILE* _File)
{
}

void qBossScript::LoadFromFile(FILE* _File)
{
}
