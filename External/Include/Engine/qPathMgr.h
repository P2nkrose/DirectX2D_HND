#pragma once

class qPathMgr : public qSingleton<qPathMgr>
{
	SINGLE(qPathMgr);

public:
	void Init();
	void Render();

public:
	const wstring& GetContentPath() { return m_Content; }
	const wstring& GetSolutionPath() { return m_Solution; }	
	static wstring GetReturnPath(const wstring& _AbsolutePath);

private:
	void GetParentPath(_Inout_ wchar_t* _Buffer);

private:
	wstring		m_Content;
	wstring		m_Solution;
};

