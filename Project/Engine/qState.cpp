#include "pch.h"
#include "qState.h"

#include "qFSM.h"



qState::qState()
	: m_Owner(nullptr)
	, m_StateType(0)
{
}

qState::~qState()
{
}

void qState::ChangeState(const wstring& _strStateName)
{
	m_Owner->ChangeState(_strStateName);
}




