#include "pch.h"
#include "qLayer.h"

#include "qGameObject.h"

qLayer::qLayer(int _LayerIdx)
	: m_LayerIdx(_LayerIdx)
{
}

qLayer::~qLayer()
{
	Delete_Vec(m_Parents);
}

void qLayer::Begin()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Begin();
	}
}

void qLayer::Tick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Tick();
	}
}

void qLayer::FinalTick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->FinalTick();
	}
}


