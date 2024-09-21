#pragma once
#include <Engine/qScript.h>

class qBleedScript : public qScript
{
public:
	CLONE(qBleedScript);
	qBleedScript();
	~qBleedScript();


public:
	virtual void Begin() override;
	virtual void Tick() override;
	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	float		m_BleedDamage;
};
