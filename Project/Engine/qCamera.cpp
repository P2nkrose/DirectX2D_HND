#include "pch.h"
#include "qCamera.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qLayer.h"
#include "qGameObject.h"


qCamera::qCamera()
	: qComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
{
}

qCamera::~qCamera()
{
}

void qCamera::Begin()
{
	// ī�޶� ���
	if (-1 != m_Priority)
	{
		
	}
}

void qCamera::FinalTick()
{
}

void qCamera::Render()
{
}
