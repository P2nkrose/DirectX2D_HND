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


private:
	vector<qCamera*>	m_vecCam;

};

