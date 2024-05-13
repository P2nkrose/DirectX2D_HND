#include "pch.h"
#include "qLevelMgr.h"

#include "qLevel.h"

qLevelMgr::qLevelMgr()
	: m_CurLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void qLevelMgr::Init()
{
	m_CurLevel = new qLevel;
}

void qLevelMgr::Progress()
{
	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}

void qLevelMgr::Render()
{
	m_CurLevel->Render();
}
