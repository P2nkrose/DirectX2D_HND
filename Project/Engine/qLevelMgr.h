#pragma once

class qLevel;

class qLevelMgr : public qSingleton<qLevelMgr>
{
	SINGLE(qLevelMgr);

public:
	void Init();
	void Progress();

public:
	qLevel* GetCurrentLevel() { return m_CurLevel; }

private:
	qLevel*		m_CurLevel;
};

