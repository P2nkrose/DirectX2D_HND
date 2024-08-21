#pragma once

class qLevel;
class qGameObject;

class qLevelMgr : public qSingleton<qLevelMgr>
{
	friend class qTaskMgr;

	SINGLE(qLevelMgr);

public:
	void Init();
	void Progress();

public:
	qLevel* GetCurrentLevel() { return m_CurLevel; }
	qGameObject* FindObjectByName(const wstring& _Name);

	void LevelChanged();
	bool IsLevelChanged() { return m_LevelChanged; }

private:
	bool ChangedLevel(qLevel* _NextLevel);

private:
	qLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];
	qLevel*		m_CurLevel;
	bool		m_LevelChanged;		// 레벨이 변경된걸 알려주는 bool 값
};

