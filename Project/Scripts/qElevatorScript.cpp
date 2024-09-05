#include "pch.h"
#include "qElevatorScript.h"

qElevatorScript::qElevatorScript()
	: qScript((UINT)SCRIPT_TYPE::ELEVATORSCRIPT)
{
}

qElevatorScript::~qElevatorScript()
{
}

void qElevatorScript::Begin()
{
}

void qElevatorScript::Tick()
{
}

void qElevatorScript::BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qElevatorScript::Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{

}

void qElevatorScript::EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider)
{
}

void qElevatorScript::SaveToFile(FILE* _File)
{
}

void qElevatorScript::LoadFromFile(FILE* _File)
{
}
