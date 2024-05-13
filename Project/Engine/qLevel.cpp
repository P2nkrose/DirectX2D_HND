#include "pch.h"
#include "qLevel.h"

#include "qLayer.h"

qLevel::qLevel()
	: m_Layer{}
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = new qLayer;
	}
}

qLevel::~qLevel()
{
	Delete_Array(m_Layer);
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
