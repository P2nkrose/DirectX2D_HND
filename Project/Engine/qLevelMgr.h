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

	void ChangeLevel(std::wstring _Name);

	void InsertLevel(wstring _Name, qLevel* _Level);

private:
	bool ChangeLevel(qLevel* _NextLevel);

private:
	//qLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];

	map<wstring, qLevel*>	m_Levels;
	qLevel*					m_CurLevel;
	bool					m_LevelChanged;		// 레벨이 변경된걸 알려주는 bool 값
};

