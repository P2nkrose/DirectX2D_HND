#pragma once

class qLevel;

class qLevelMgr : public qSingleton<qLevelMgr>
{
	SINGLE(qLevelMgr);

public:
	void Init();
	void Progress();
	void Render();

private:
	qLevel*		m_CurLevel;
};

