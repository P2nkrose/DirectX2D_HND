#pragma once
#include "singleton.h"

class qCamera;
class qGameObject;

class qRenderMgr : public qSingleton<qRenderMgr>
{
	SINGLE(qRenderMgr)

public:
	void Init();
	void Tick();

	void RegisterCamera(qCamera* _Cam, int _CamPriority);
	void RegisterEditorCamera(qCamera* _Cam) { m_EditorCamera = _Cam; }
	void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeList.push_back(_Info); }


private:
	void RenderDebugShape();


private:
	vector<qCamera*>			m_vecCam;
	qCamera*					m_EditorCamera;

	qGameObject*				m_DebugObject;
	list<tDebugShapeInfo>		m_DebugShapeList;
};

