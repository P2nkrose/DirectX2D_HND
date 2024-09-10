#include "pch.h"
#include "qDrownedScript.h"

qDrownedScript::qDrownedScript()
	: qScript((UINT)SCRIPT_TYPE::DROWNEDSCRIPT)
{
}

qDrownedScript::~qDrownedScript()
{
}

void qDrownedScript::Begin()
{
}

void qDrownedScript::Tick()
{
}

void qDrownedScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qDrownedScript::SaveToFile(FILE* _File)
{
}

void qDrownedScript::LoadFromFile(FILE* _File)
{
}

void qDrownedScript::Hit(float _Damage)
{
}
