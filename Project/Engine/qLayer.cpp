#include "pch.h"
#include "qLayer.h"

#include "qGameObject.h"

qLayer::qLayer()
{
}

qLayer::~qLayer()
{
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

void qLayer::Render()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Render();
	}
}
