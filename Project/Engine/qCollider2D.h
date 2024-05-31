#pragma once
#include "qComponent.h"

class qCollider2D : public qComponent
{
public:
	CLONE(qCollider2D);
	qCollider2D();
	~qCollider2D();


public:
	virtual void FinalTick() override;

public:
	virtual void BeginOverlap(qCollider2D* _Other);
	virtual void Overlap(qCollider2D* _Other);
	virtual void EndOverlap(qCollider2D* _Other);


public:
	void SetOffset(Vec3 _Offset) { m_Offset = _Offset; }
	void SetScale(Vec3 _Scale) { m_Scale = _Scale; }

	Vec3 GetOffset() { return m_Offset; }
	Vec3 GetScale() { return m_Scale; }
	Vec3 GetFinalPos() { return m_FinalPos; }
	int GetOverlapCount() { return m_OverlapCount; }


private:
	Vec3		m_Offset;
	Vec3		m_Scale;
	Vec3		m_FinalPos;
	int			m_OverlapCount;

};

