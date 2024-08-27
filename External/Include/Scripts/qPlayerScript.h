#pragma once
#include <Engine/qScript.h>

class qGameObject;

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
	virtual void Overlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;
	virtual void EndOverlap(qCollider2D* _OwnCollider, qGameObject* _OtherObject, qCollider2D* _OtherCollider) override;

public:
	void SetPlayerDir(DIRECTION _Dir) { m_CurUnitInfo.Dir = _Dir; }

	bool IsDirChanged() { return m_DirChanged; }

	bool IsDash() { return m_IsDash; }
	bool IsDashCoolTime() { return m_IsDashCoolTime; }

	void SetDash(bool _IsDash) { m_IsDash = _IsDash; m_IsDashCoolTime = _IsDash; }
	void SetLock(bool _Lock) { m_DirLock = _Lock; }

	void ResetCombo() { m_NextCombo = 1; }

	DIRECTION GetPlayerDir() { return m_CurUnitInfo.Dir; }
	tUnitInfo& GetPrevInfo() { return m_PrevUnitInfo; }
	tUnitInfo& GetUnitInfo() { return m_CurUnitInfo; }


public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;
	void PlayCombo();

	
	void Jump();
	void RestoreJumpCount()
	{
		m_CurJumpCount = 0;
	}




private:
	tUnitInfo			m_CurUnitInfo;
	tUnitInfo			m_PrevUnitInfo;


	Vec3				m_PlayerPos;
	Vec3				m_PlayerRot;

	float				m_Speed;
	Ptr<qTexture>		m_Texture;
	Ptr<qPrefab>		m_MissilePref;

	DIRECTION			m_PlayerDir;
	float				m_Dir;

	bool				m_DirLock;
	bool				m_DirChanged;
	bool				m_IsDash;
	bool				m_IsDashCoolTime;

	float				m_DashCoolTime;

	int					m_NextCombo;

	int					m_CurJumpCount;
	int					m_DoubleJumpCount;
};

