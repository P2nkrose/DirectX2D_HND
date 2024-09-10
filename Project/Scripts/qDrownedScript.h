#pragma once
#include <Engine/qScript.h>

class qGameObject;

class qDrownedScript : public qScript
{
public:
	CLONE(qDrownedScript);
	qDrownedScript();
	~qDrownedScript();

public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

	virtual void Hit(float _Damage) override;

public:
	void SetDrownedDir(DIRECTION _Dir) { m_CurUnitInfo.Dir = _Dir; }
	bool IsDirChanged() { return m_DirChanged; }
	DIRECTION GetDrownedDir() { return m_CurUnitInfo.Dir; }
	tUnitInfo GetPrevInfo() { return m_PrevUnitInfo; }
	tUnitInfo GetUnitInfo() { return m_CurUnitInfo; }


private:
	Vec3		m_DrownedPos;
	Vec3		m_DrownedRot;

	DIRECTION	m_SkeletonDir;

	bool		m_DirChanged;
};

