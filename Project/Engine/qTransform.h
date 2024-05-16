#pragma once
#include "qComponent.h"


class qTransform : public qComponent
{
public:
	virtual qTransform* Clone() { return new qTransform; }
	qTransform();
	~qTransform();

	virtual void FinalTick() override;
	void Binding();

public:
	void SetRelativePos(Vec3 _Pos) { m_RelativePos = _Pos; }
	void SetRelativeScale(Vec3 _Scale) { m_RelativeScale = _Scale; }
	void SetRelativeRotation(Vec3 _Rot) { m_RelativeRotation = _Rot; }

	void SetRelativePos(float x, float y, float z) { m_RelativePos = Vec3(x, y, z); }
	void SetRelativeScale(float x, float y, float z) { m_RelativeScale = Vec3(x, y, z); }
	void SetRelativeRotation(float x, float y, float z) { m_RelativeRotation = Vec3(x, y, z); }

	Vec3 GetRelativePos() { return m_RelativePos; }
	Vec3 GetRelativeScale() { return m_RelativeScale; }
	Vec3 GetRelativeRotation() { return m_RelativeRotation; }


private:
	Vec3	m_RelativePos;
	Vec3	m_RelativeScale;
	Vec3	m_RelativeRotation;
};

