#include "pch.h"
#include "qLevel.h"

#include "qLayer.h"

qLevel::qLevel()
	: m_Layer{}
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

void qLevel::Render()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Render();
	}
}

void qLevel::AddObject(int LayerIdx, qGameObject* _Object)
{
	m_Layer[LayerIdx]->AddObject(_Object);
}
