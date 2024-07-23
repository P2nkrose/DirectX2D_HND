#pragma once
#include <Engine/qScript.h>

class qPlayerScript : public qScript
{
public:
	CLONE(qPlayerScript);
	qPlayerScript();
	~qPlayerScript();

public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void BeginOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;


private:
	float				m_Speed;
	Ptr<qTexture>		m_Texture;
	Ptr<qPrefab>		m_MissilePref;
};

