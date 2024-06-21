#pragma once

class qLevel;
class qGameObject;

class qLevelMgr : public qSingleton<qLevelMgr>
{
	SINGLE(qLevelMgr);

public:
	void Init();
	void Progress();

public:
	qLevel* GetCurrentLevel() { return m_CurLevel; }
	qGameObject* FindObjectByName(const wstring& _Name);

private:
	qLevel*		m_CurLevel;
};

