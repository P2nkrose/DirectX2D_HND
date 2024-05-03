#include "pch.h"
#include "qEngine.h"

#include "qDevice.h"
#include "Temp.h"

qEngine::qEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{
}

qEngine::~qEngine()
{
	TempRelease();
}

int qEngine::Init(HWND _wnd, POINT _ptResolution)
{
	m_hWnd = _wnd;
	m_ptResolution = _ptResolution;
	ChangeWindowScale(_ptResolution.x, _ptResolution.y);

	if (FAILED(qDevice::GetInst()->Init(m_hWnd, m_ptResolution.x, m_ptResolution.y)))
	{
		MessageBox(nullptr, L"장치 초기화 실패", L"CDevice 초기화 실패", MB_OK);
		return E_FAIL;
	}

	TempInit();

	return S_OK;
}

void qEngine::Progress()
{
	TempTick();
	
	qDevice::GetInst()->Clear();

	TempRender();

	qDevice::GetInst()->Present();
}


void qEngine::ChangeWindowScale(UINT _Width, UINT _Height)
{
	bool bMenu = false;
	if (GetMenu(m_hWnd))
		bMenu = true;

	RECT rt = { 0, 0, _Width, _Height };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, bMenu);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}