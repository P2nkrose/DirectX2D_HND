#include "pch.h"
#include "qLevel.h"

#include "qLayer.h"

qLevel::qLevel()
	: m_Layer{}
	, m_State(LEVEL_STATE::STOP)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = new qLayer(i);
	}
}

qLevel::~qLevel()
{
	Delete_Array(m_Layer);
}

void qLevel::Begin()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Begin();
	}
}

void qLevel::Tick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Tick();
	}
}

void qLevel::FinalTick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->FinalTick();
	}
}

void qLevel::ClearObject()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->ClearObject();
	}
}


void qLevel::AddObject(int LayerIdx, qGameObject* _Object, bool _bMoveChild)
{
	m_Layer[LayerIdx]->AddObject(_Object, _bMoveChild);
}

void qLevel::ChangeState(LEVEL_STATE _NextState)
{
	if (m_State == _NextState)
		return;

	// Stop -> Pause (X)
	if (STOP == m_State && PAUSE == _NextState)
		return;

	// Stop -> Play (���� ������ ������ ���۵Ǹ�, ������ �ִ� ��ü���� Begin �� ȣ��Ǿ�� �Ѵ�.)
	if (STOP == m_State && PLAY == _NextState)
	{
		Begin();
	}

	m_State = _NextState;

	// Play -> Stop (���� ������ ���۵Ǵ� �������� ������ �����ؾ� �Ѵ�.)
}
