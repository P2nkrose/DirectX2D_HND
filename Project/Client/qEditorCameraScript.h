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
	void OrthoGraphicMove();		// ���� ����
	void PerspectiveMove();			// ���� ����

private:
	float		m_Speed;

};

