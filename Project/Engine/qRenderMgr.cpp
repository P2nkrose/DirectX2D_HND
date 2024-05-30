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
	// ī�޶� �켱 ������ ���� ������ ������ ���õǾ�� �Ѵ�.
	if (m_vecCam.size() <= _CamPriority + 1)
		m_vecCam.resize(_CamPriority + 1);

	// ī�޶� �켱 ������ �´� ��ġ�� �ִ´�.
	m_vecCam[_CamPriority] = _Cam;
}


void qRenderMgr::RenderDebugShape()
{
}
