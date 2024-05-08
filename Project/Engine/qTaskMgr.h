#pragma once


class qTaskMgr : public qSingleton<qTaskMgr>
{
	SINGLE(qTaskMgr)
private:
	vector<tTask>	m_vecTask;
	vector<CObj*>	m_GC; // Garbage Collector;

public:
	void tick();
	void AddTask(const tTask& _Task) { m_vecTask.push_back(_Task); }

private:
	void ClearGC();
	void ExecuteTask();	
};

