#pragma once

// DirectX 관련 기능을 담당
// GPU 제어

class qDevice : public qSingleton<qDevice>
{
	SINGLE(qDevice);
	

public:
	int Init(HWND _hWnd, UINT _Width, UINT _Height);
	void Clear();
	void Present() { m_SwapChain->Present(0, 0); }

public:
	ID3D11Device* GetDevice() { return m_Device; }
	ID3D11DeviceContext* GetContext() { return m_Context; }

private:
	int CreateSwapChain();
	int CreateView();


private:
	HWND						m_hWnd;
	Vec2						m_vResolution;

	ID3D11Device*				m_Device;		// Dx 11 객체 생성, GPU 메모리 할당
	ID3D11DeviceContext*		m_Context;		// Rendering

	IDXGISwapChain*				m_SwapChain;	// 렌더링된 이미지를 사용자에게 표시

	ID3D11Texture2D*			m_RTTex;		// 랜더타겟 텍스처 텍스처 리소스의 속성을 가져옴
	ID3D11Texture2D*			m_DSTex;		// 텍스처 리소스의 속성을 가져옴

	ID3D11RenderTargetView*		m_RTView;		// 리소스 데이터에 액세스하기 위한 렌더링 대상 뷰를 만듬
	ID3D11DepthStencilView*		m_DSView;		// 깊이 스텐실 테스트 중에 텍스처 리소스에 액세스함

	ID3D11BlendState*			m_BSState;		// 혼합 상태 인터페이스는 출력 병합기에 바인딩할 수 있는 혼합 상태에 대한 설명을 포함
	ID3D11DepthStencilState*	m_DSState;		// 깊이 스텐실 테스트 중에 텍스처 리소스에 액세스함
	ID3D11SamplerState*			m_Sampler;		// 샘플러 상태 인터페이스에는 텍스처 샘플 작업에서 참조하기 위해 파이프라인 의 셰이더 단계에 바인딩할 수 있는 샘플러 상태에 대한 설명
	ID3D11RasterizerState*		m_RSState;
};

