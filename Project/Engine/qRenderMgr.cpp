#include "pch.h"
#include "qRenderMgr.h"

#include "qCamera.h"

qRenderMgr::qRenderMgr()
{

}

qRenderMgr::~qRenderMgr()
{

}


void qRenderMgr::Init()
{
}

void qRenderMgr::Tick()
{
	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		if (nullptr == m_vecCam[i])
			continue;

		m_vecCam[i]->Render();
	}

	RenderDebugShape();
}

void qRenderMgr::RegisterCamera(qCamera* _Cam, int _CamPriority)
{
	// 카메라 우선 순위에 따라서 벡터의 공간이 마련되어야 한다.
	if (m_vecCam.size() <= _CamPriority + 1)
		m_vecCam.resize(_CamPriority + 1);

	// 카메라 우선 순위에 맞는 위치에 넣는다.
	m_vecCam[_CamPriority] = _Cam;
}


void qRenderMgr::RenderDebugShape()
{
}
