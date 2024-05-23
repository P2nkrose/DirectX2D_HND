#pragma once

#include "qTexture.h"

// DirectX ���� ����� ���
// GPU ����
class qConstBuffer;

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

	qConstBuffer* GetConstBuffer(CB_TYPE _Type) { return m_arrCB[(UINT)_Type]; }
	ID3D11RasterizerState* GetRSState(RS_TYPE _Type) { return m_RSState[(UINT)_Type].Get(); }

public:
	Vec2 GetResolution() { return m_vResolution; }

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();
	int CreateRasterizeState();


private:
	HWND								m_hWnd;
	Vec2								m_vResolution;


	ComPtr<ID3D11Device>				m_Device;		// Dx 11 ��ü ����, GPU �޸� �Ҵ�
	ComPtr<ID3D11DeviceContext>			m_Context;		// Rendering

	ComPtr<IDXGISwapChain>				m_SwapChain;	// �������� �̹����� ����ڿ��� ǥ��

	ComPtr<ID3D11Texture2D>				m_RTTex;		// ����Ÿ�� �ؽ�ó �ؽ�ó ���ҽ��� �Ӽ��� ������
	ComPtr<ID3D11RenderTargetView>		m_RTView;		// ���ҽ� �����Ϳ� �׼����ϱ� ���� ������ ��� �並 ����

	Ptr<qTexture>						m_DSTex;		// �ؽ�ó ���ҽ��� �Ӽ��� ������

	ComPtr<ID3D11RasterizerState>		m_RSState[(UINT)RS_TYPE::END];	// �����Ͷ����� Ÿ���� ���ϱ�(�ø� ���ϱ�)

	ComPtr<ID3D11BlendState>			m_BSState;		// ȥ�� ���� �������̽��� ��� ���ձ⿡ ���ε��� �� �ִ� ȥ�� ���¿� ���� ������ ����
	ComPtr<ID3D11DepthStencilState>		m_DSState;		// ���� ���ٽ� �׽�Ʈ �߿� �ؽ�ó ���ҽ��� �׼�����
	ComPtr<ID3D11SamplerState>			m_Sampler;		// ���÷� ���� �������̽����� �ؽ�ó ���� �۾����� �����ϱ� ���� ���������� �� ���̴� �ܰ迡 ���ε��� �� �ִ� ���÷� ���¿� ���� ����


	qConstBuffer*						m_arrCB[(UINT)CB_TYPE::END];
};

