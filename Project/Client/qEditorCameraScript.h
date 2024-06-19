#pragma once
#include <Engine/qScript.h>


class qEditorCameraScript : public qScript
{
public:
	CLONE(qEditorCameraScript);
	qEditorCameraScript();
	~qEditorCameraScript();


public:
	virtual void Tick() override;

private:
	void OrthoGraphicMove();		// 직교 투영
	void PerspectiveMove();			// 원근 투영

private:
	float		m_Speed;

};

