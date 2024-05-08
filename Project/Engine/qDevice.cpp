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
	, m_DSView(nullptr)
	, m_RTView(nullptr)
	, m_hWnd(nullptr)
{

}

qDevice::~qDevice()
{
	if (nullptr != m_Device)
		m_Device->Release();

	if (nullptr != m_Context)
		m_Context->Release();

	if (nullptr != m_SwapChain)
		m_SwapChain->Release();

	if (nullptr != m_RTTex)
		m_RTTex->Release();

	if (nullptr != m_DSTex)
		m_DSTex->Release();

	if (nullptr != m_RTView)
		m_RTView->Release();

	if (nullptr != m_DSView)
		m_DSView->Release();
	
}

int qDevice::Init(HWND _hWnd, UINT _Width, UINT _Height)
{
	// 윈도우 핸들 및 해상도 값 저장
	m_hWnd = _hWnd;

	m_vResolution.x = (float)_Width;
	m_vResolution.y = (float)_Height;

	
	// Device, Context 생성
	UINT Flag = 0;

#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
							   , nullptr, Flag
							   , nullptr, 0
							   , D3D11_SDK_VERSION
							   , &m_Device, nullptr, &m_Context)))
	{
		MessageBox(nullptr, L"Device, Context 생성 실패", L"장치초기화 실패", MB_OK);
		return E_FAIL;
	}


	// Swap Chain
	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// RenderTargetView, DepthStencilView
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"View 생성 실패", L"장치 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Output Merge State (출력 병합 단계)
	m_Context->OMSetRenderTargets(1, &m_RTView, m_DSView);


	// ViewPort 설정
	// 출력시킬 화면 윈도우 영역을 설정
	D3D11_VIEWPORT viewport = {};

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_vResolution.x;
	viewport.Height = m_vResolution.y;

	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.f;

	CONTEXT->RSSetViewports(1, &viewport);


	return S_OK;
}

void qDevice::Clear()
{
	float color[4] = { 0.4f, 0.4f, 0.4f, 1.f };
	m_Context->ClearRenderTargetView(m_RTView, color);
	m_Context->ClearDepthStencilView(m_DSView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

int qDevice::CreateSwapChain()
{
	// Swap Chain : 화면에 그림을 그리기 위한 버퍼를 관리하고,
	//				버퍼에 그려진 이미지를 화면 출력을 담당하는 객체
	DXGI_SWAP_CHAIN_DESC Desc = {};

	Desc.BufferCount						= 1;				// 백버퍼 갯수
	Desc.BufferDesc.Width					= m_vResolution.x;	// 백버퍼 해상도
	Desc.BufferDesc.Height					= m_vResolution.y;	// 백버퍼 해상도
	Desc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;	// 픽셀 포맷
	Desc.BufferDesc.RefreshRate.Denominator = 60;	// 화면 갱신률
	Desc.BufferDesc.RefreshRate.Numerator	= 1;
	Desc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.BufferDesc.ScanlineOrdering		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Desc.BufferUsage						= DXGI_USAGE_RENDER_TARGET_OUTPUT;		// 버퍼의 사용 용도 (Render Target)
	Desc.Windowed							= true;	// 창모드 설정
	Desc.OutputWindow						= m_hWnd;		// SwapChain 버퍼의 이미지를 출력시킬 윈도우 핸들
	Desc.Flags								= 0;
	Desc.SampleDesc.Count					= 1;
	Desc.SampleDesc.Quality					= 0;
	Desc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;


	IDXGIDevice* Device = nullptr;
	IDXGIAdapter* Adapter = nullptr;
	IDXGIFactory* Factory = nullptr;

	if (FAILED(m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&Device)))
		return E_FAIL;

	if (FAILED(Device->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter)))
		return E_FAIL;

	if (FAILED(Adapter->GetParent(_uuidof(IDXGIFactory), (void**)&Factory)))
		return E_FAIL;

	if (FAILED(Factory->CreateSwapChain(m_Device, &Desc, &m_SwapChain)))
		return E_FAIL;


	Device->Release();
	Adapter->Release();
	Factory->Release();


	return S_OK;
}

int qDevice::CreateView()
{
	// ===========================================================
	//   RenderTarget Texture, DepthStencil Texture 를 생성시킨다.
	// ===========================================================

	// Swap Chain의 백버퍼 주소를 받아온다.
	m_SwapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), (void**)&m_RTTex);

	// Depth Stencil Texture 생성
	D3D11_TEXTURE2D_DESC Desc = {};

	Desc.Width				= m_vResolution.x;	// DepthStencil 텍스쳐는 Render Target 해상도와 반드시 일치해야 한다.
	Desc.Height				= m_vResolution.y;
	Desc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;	// Depth 24bit, Stencil 8bit
	Desc.ArraySize			= 1;
	Desc.BindFlags			= D3D11_BIND_DEPTH_STENCIL;

	Desc.Usage				= D3D11_USAGE_DEFAULT;	// System Memory 와의 연계 설정
	Desc.CPUAccessFlags		= 0;

	Desc.MiscFlags			= 0;
	Desc.MipLevels			= 1;		// 열화버전(낮은 해상도) 이미지 추가 생성

	Desc.SampleDesc.Count	= 1;
	Desc.SampleDesc.Quality = 0;

	if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, &m_DSTex)))
	{
		MessageBox(nullptr, L"DepthStencil 텍스쳐 생성 실패", L"View 생성 실패", MB_OK);
		return E_FAIL;
	}


	// ===========================================
	//    RenderTargetView, DepthStencilView 생성
	// ===========================================

	if (FAILED(m_Device->CreateRenderTargetView(m_RTTex, nullptr, &m_RTView)))
	{
		MessageBox(nullptr, L"RenderTargetView 생성 실패", L"View 생성 실패", MB_OK);
		return E_FAIL;
	}

	if (FAILED(m_Device->CreateDepthStencilView(m_DSTex, nullptr, &m_DSView)))
	{
		MessageBox(nullptr, L"DepthStencilView 생성 실패", L"View 생성 실패", MB_OK);
		return E_FAIL;
	}

	// View에는 여러가지 종류가 있음
	// RenderTargetView
	// DepthStencilView
	// ShaderResourceView
	// UnorderedAccessView


	return S_OK;
}
