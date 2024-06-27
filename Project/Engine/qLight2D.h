#pragma once
#include "qComponent.h"

class qLight2D : public qComponent
{
public:
	CLONE(qLight2D);
	qLight2D();
	~qLight2D();

public:
	virtual void FinalTick() override;

public:
	void SetLightType(LIGHT_TYPE _Type);
	void SetRadius(float _Radius) { m_Info.Radius = _Radius; }
	void SetAngle(float _Angle) { m_Info.Angle = _Angle; }

	LIGHT_TYPE GetLightType() { return m_Info.Type; }
	float GetRadius() { return m_Info.Radius; }
	float GetAngle() { return m_Info.Angle; }

	const tLightInfo& GetLightInfo() { return m_Info; }


private:
	tLightInfo		m_Info;
};

