#pragma once

class qPathMgr : public qSingleton<qPathMgr>
{
	SINGLE(qPathMgr);
private:
	wstring		m_Content;
	wstring		m_Solution;


public:
	void Init();
	void render();

private:
	void GetParentPath(_Inout_ wchar_t* _Buffer);

public:
	const wstring& GetContentPath() { return m_Content; }
	const wstring& GetSolutionPath() { return m_Solution; }	
};

