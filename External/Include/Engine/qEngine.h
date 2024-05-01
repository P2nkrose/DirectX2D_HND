#pragma once


class qEngine : public qSingleton<qEngine>
{
	SINGLE(qEngine);


private:
	HWND			m_hWnd;
	POINT			m_ptResolution;

public:
	int Init(HWND _wnd, POINT _ptResolution);
	void Progress();
	void ChangeWindowScale(UINT _Width, UINT _Height);
};

