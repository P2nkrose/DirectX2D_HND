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
	// 카메라를 등록
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
