#include "pch.h"
#include "qState.h"

qState::qState()
{
}

qState::~qState()
{
}

void qState::ChangeState(const wstring& _strStateName)
{
	m_Owner->ChangeState(_strStateName);
}

