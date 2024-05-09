#include "pch.h"
#include "Temp.h"

#include "qDevice.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"

// Vertex Buffer ���ؽ� ����
ComPtr<ID3D11Buffer>	g_VB = nullptr;

// �ε��� ����
ComPtr<ID3D11Buffer>	g_IB = nullptr;

Vtx		g_Vtx[4] = {};
UINT	g_Idx[6] = {};


// ���ؽ� ���̴� (Vertex Shader) ����
ComPtr<ID3DBlob>				g_VSBlob = nullptr;
ComPtr<ID3D11VertexShader>		g_VS = nullptr;

// �ȼ� ���̴� (Pixel Shader) ����
ComPtr<ID3DBlob>				g_PSBlob = nullptr;
ComPtr<ID3D11PixelShader>		g_PS = nullptr;

ComPtr<ID3DBlob>				g_ErrBlob = nullptr;

// ���̾ƿ� (InputLayout)
ComPtr<ID3D11InputLayout>		g_Layout = nullptr;

int TempInit()
{
	// ���ؽ� ���� ����
	// 0 --- 1
	// |  \  |
	// 3 --- 2
	g_Vtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	g_Vtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_Vtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_Vtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_Vtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_Vtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_Vtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	g_Vtx[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);


	D3D11_BUFFER_DESC tVtxBufferDesc = {};

	tVtxBufferDesc.ByteWidth = sizeof(Vtx) * 4;				// ���ؽ����۵���ũ�� ũ��
	tVtxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���ؽ������� �뵵

	// Vertex Buffer�� ������ ���Ŀ��� ������ ���Ⱑ �����ϵ��� ����
	tVtxBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tVtxBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	tVtxBufferDesc.MiscFlags = 0;
	tVtxBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_Vtx;

	if (FAILED(DEVICE->CreateBuffer(&tVtxBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		MessageBox(nullptr, L"VertexBuffer ���� ����", L"Temp �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// ====================
	//   Index Buffer ����
	// ====================

	g_Idx[0] = 0;		g_Idx[1] = 1;		g_Idx[2] = 2;
	g_Idx[3] = 0;		g_Idx[4] = 2;		g_Idx[5] = 3;

	D3D11_BUFFER_DESC IdxBufferDesc = {};

	IdxBufferDesc.ByteWidth = sizeof(UINT) * 6;
	IdxBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// Index ���۰� ������ ���Ŀ� �����Ͱ� ����� ���� ����.
	IdxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IdxBufferDesc.CPUAccessFlags = 0;

	IdxBufferDesc.MiscFlags = 0;
	IdxBufferDesc.StructureByteStride = 0;

	tSub.pSysMem = g_Idx;

	if (FAILED(DEVICE->CreateBuffer(&IdxBufferDesc, &tSub, g_IB.GetAddressOf())))
	{
		MessageBox(nullptr, L"IndexBuffer ���� ����", L"Temp �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// ===================
	//  Vertex Shader ����
	// ===================
	wstring strShaderPath = qPathMgr::GetInst()->GetContentPath();


	HRESULT hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
								    , nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
								    , "VS_Test", "vs_5_0", D3DCOMPILE_DEBUG, 0
									, g_VSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf());


	if (FAILED(hr))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "���̴� ������ ����", MB_OK);
		}
		else
		{
			errno_t err = GetLastError();
			WCHAR szErrMsg[255] = {};
			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);
			MessageBox(nullptr, szErrMsg, L"���̴� ������ ����", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer()
							 , g_VSBlob->GetBufferSize()
							 , nullptr, g_VS.GetAddressOf());


	// ===================
	//  Pixel Shader ����
	// ===================

	hr = D3DCompileFromFile((strShaderPath + L"shader\\test.fx").c_str()
		, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Test", "ps_5_0", D3DCOMPILE_DEBUG, 0
		, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr, (char*)g_ErrBlob->GetBufferPointer(), "���̴� ������ ����", MB_OK);
		}
		else
		{
			errno_t err = GetLastError();
			wchar_t szErrMsg[255] = {};
			swprintf_s(szErrMsg, 255, L"Error Code : %d", err);
			MessageBox(nullptr, szErrMsg, L"���̴� ������ ����", MB_OK);
		}

		return E_FAIL;
	}

	DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer()
		, g_PSBlob->GetBufferSize(), nullptr, g_PS.GetAddressOf());


	// ===================
	//     Layout ����
	// ===================
	D3D11_INPUT_ELEMENT_DESC Element[2] = {};

	Element[0].AlignedByteOffset = 0;						
	Element[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	Element[0].InputSlot = 0;
	Element[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[0].InstanceDataStepRate = 0;
	Element[0].SemanticName = "POSITION";
	Element[0].SemanticIndex = 0;

	Element[1].AlignedByteOffset = 12;							
	Element[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	Element[1].InputSlot = 0;
	Element[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	Element[1].InstanceDataStepRate = 0;
	Element[1].SemanticName = "COLOR";
	Element[1].SemanticIndex = 0;

	

	DEVICE->CreateInputLayout(Element, 2
							, g_VSBlob->GetBufferPointer()
							, g_VSBlob->GetBufferSize()
							, g_Layout.GetAddressOf());
	 
	return S_OK;
}

void TempTick()
{
	float dt = qTimeMgr::GetInst()->GetDeltaTime();

	if (qKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
	{
		for (int i = 0; i < 4; ++i)
		{
			g_Vtx[i].vPos.x -= dt * 1.f;
		}
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		for (int i = 0; i < 4; ++i)
		{
			g_Vtx[i].vPos.x += dt * 1.f;
		}
	}

	// ���������� �ִ� ���� �����͸� ���ؽ����۷� ����
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);

	memcpy(tMapSub.pData, g_Vtx, sizeof(Vtx) * 4);

	CONTEXT->Unmap(g_VB.Get(), 0);
}

void TempRender()
{
	UINT stride = sizeof(Vtx);
	UINT offset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &stride, &offset);
	CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
	CONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	// 3���� ���� �ϳ��� �ﰢ������ �ؼ�
	CONTEXT->IASetInputLayout(g_Layout.Get());

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	//CONTEXT->Draw(6, 0);
	CONTEXT->DrawIndexed(6, 0, 0);
}

void TempRelease()
{
	
}

