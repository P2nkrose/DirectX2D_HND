#pragma once

// DirectX ���� ����� ���
// GPU ����

class qDevice : public qSingleton<qDevice>
{
	SINGLE(qDevice);
	

public:
	int Init(HWND _hWnd, UINT _Width, UINT _Height);
	void Clear();
	void Present() { m_SwapChain->Present(0, 0); }

public:
	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

private:
	int CreateSwapChain();
	int CreateView();


private:
	HWND								m_hWnd;
	Vec2								m_vResolution;


	ComPtr<ID3D11Device>				m_Device;		// Dx 11 ��ü ����, GPU �޸� �Ҵ�
	ComPtr<ID3D11DeviceContext>			m_Context;		// Rendering

	ComPtr<IDXGISwapChain>				m_SwapChain;	// �������� �̹����� ����ڿ��� ǥ��

	ComPtr<ID3D11Texture2D>				m_RTTex;		// ����Ÿ�� �ؽ�ó �ؽ�ó ���ҽ��� �Ӽ��� ������
	ComPtr<ID3D11Texture2D>				m_DSTex;		// �ؽ�ó ���ҽ��� �Ӽ��� ������

	ComPtr<ID3D11RenderTargetView>		m_RTView;		// ���ҽ� �����Ϳ� �׼����ϱ� ���� ������ ��� �並 ����
	ComPtr<ID3D11DepthStencilView>		m_DSView;		// ���� ���ٽ� �׽�Ʈ �߿� �ؽ�ó ���ҽ��� �׼�����

	ComPtr<ID3D11BlendState>			m_BSState;		// ȥ�� ���� �������̽��� ��� ���ձ⿡ ���ε��� �� �ִ� ȥ�� ���¿� ���� ������ ����
	ComPtr<ID3D11DepthStencilState>		m_DSState;		// ���� ���ٽ� �׽�Ʈ �߿� �ؽ�ó ���ҽ��� �׼�����
	ComPtr<ID3D11SamplerState>			m_Sampler;		// ���÷� ���� �������̽����� �ؽ�ó ���� �۾����� �����ϱ� ���� ���������� �� ���̴� �ܰ迡 ���ε��� �� �ִ� ���÷� ���¿� ���� ����
	ComPtr<ID3D11RasterizerState>		m_RSState;
};

