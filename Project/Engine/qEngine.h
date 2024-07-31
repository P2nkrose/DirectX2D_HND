#pragma once

typedef void(*OBJECT_SAVE)(FILE*, class qGameObject*);
typedef qGameObject* (*OBJECT_LOAD)(FILE*);


class qEngine : public qSingleton<qEngine>
{
	SINGLE(qEngine);


public:
	int Init(HWND _wnd, POINT _ptResolution, OBJECT_SAVE _SaveFunc, OBJECT_LOAD _Func);
	void Progress();
	void ChangeWindowScale(UINT _Width, UINT _Height);

public:
	HWND GetMainWnd() { return m_hWnd; }


private:
	HWND			m_hWnd;
	POINT			m_ptResolution;
};

