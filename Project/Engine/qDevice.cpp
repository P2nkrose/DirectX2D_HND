#include "pch.h"
#include "qDevice.h"

qDevice::qDevice()
	: m_Device(nullptr)
	, m_Context(nullptr)
	, m_SwapChain(nullptr)
	, m_RTTex(nullptr)
	, m_DSTex(nullptr)
	, m_BSState(nullptr)
	, m_DSState(nullptr)
	, m_Sampler(nullptr)
	, m_RSState(nullptr)
{

}

qDevice::~qDevice()
{

}

int qDevice::Init(HWND _hWnd, UINT _Width, UINT _Height)
{
	return S_OK;
}
