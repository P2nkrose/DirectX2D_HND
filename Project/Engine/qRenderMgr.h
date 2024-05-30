#pragma once
#include "singleton.h"

class qCamera;

class qRenderMgr : public qSingleton<qRenderMgr>
{
	SINGLE(qRenderMgr)

public:
	void Init();
	void Tick();

	void RegisterCamera(qCamera* _Cam, int _CamPriority);
	void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeList.push_back(_Info); }


private:
	void RenderDebugShape();


private:
	vector<qCamera*>			m_vecCam;
	list<tDebugShapeInfo>		m_DebugShapeList;
};

