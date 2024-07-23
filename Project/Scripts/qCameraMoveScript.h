#pragma once
#include <Engine/qScript.h>

class qCameraMoveScript : public qScript
{
public:
	CLONE(qCameraMoveScript);
	qCameraMoveScript();
	~qCameraMoveScript();

	virtual void Tick() override;

public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	void OrthoGraphicMove();
	void PerspectiveMove();


private:
	float		m_CamSpeed;
};

