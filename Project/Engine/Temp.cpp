#include "pch.h"
#include "Temp.h"

#include "qDevice.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"

#include "qEntity.h"
#include "qMesh.h"

tTransform g_ObjTrans = {};

qMesh* g_Mesh = nullptr;



// ���ؽ� ���̴� (Vertex Shader) ����
ComPtr<ID3DBlob>				g_VSBlob = nullptr;
ComPtr<ID3D11VertexShader>		g_VS = nullptr;

// �ȼ� ���̴� (Pixel Shader) ����
ComPtr<ID3DBlob>				g_PSBlob = nullptr;
ComPtr<ID3D11PixelShader>		g_PS = nullptr;

ComPtr<ID3DBlob>				g_ErrBlob = nullptr;

// ���̾ƿ� (InputLayout)
ComPtr<ID3D11InputLayout>		g_Layout = nullptr;


// ��� ���� (Constant Buffer)
ComPtr<ID3D11Buffer>			g_CB = nullptr;





int TempInit()
{
	g_ObjTrans.Scale = Vec4(1.2f, 1.2f, 1.2f, 1.f);

	// RectMesh ����
	// 0 --- 1
	// |  \  |
	// 3 --- 2


	// Vertex
	Vtx arrVtx[4] = {};

	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	// Index ���� ����
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;		arrIdx[1] = 1;		arrIdx[2] = 2;
	arrIdx[3] = 0;		arrIdx[4] = 2;		arrIdx[5] = 3;

	g_Mesh = new qMesh;
	g_Mesh->Create(arrVtx, 4, arrIdx, 6);

		



	// ====================
	//   ��� Buffer ����
	// ====================

	D3D11_BUFFER_DESC tCBDesc = {};

	tCBDesc.ByteWidth = sizeof(tTransform);
	tCBDesc.Usage = D3D11_USAGE_DYNAMIC;
	tCBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tCBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (FAILED(DEVICE->CreateBuffer(&tCBDesc, nullptr, g_CB.GetAddressOf())))
	{
		MessageBox(nullptr, L"ConstantBuffer ���� ����", L"Temp �ʱ�ȭ ����", MB_OK);
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
		g_ObjTrans.Pos.x -= dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.x += dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.y += dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
	{
		g_ObjTrans.Pos.y -= dt * 1.f;
	}



	// ���������� �ִ� ���� �����͸� ���ؽ����۷� ����
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);

	memcpy(tMapSub.pData, &g_ObjTrans, sizeof(tTransform));

	CONTEXT->Unmap(g_CB.Get(), 0);
}

void TempRender()
{
	CONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	// 3���� ���� �ϳ��� �ﰢ������ �ؼ�
	CONTEXT->IASetInputLayout(g_Layout.Get());

	// ������� ���ε�, b0 �������Ϳ�, Vertex Shader ������, g_CB �� �ִ� ���� 0�� �������Ϳ� ���ε� �� ����
	CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());


	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	g_Mesh->render();
}

void TempRelease()
{
	delete g_Mesh;
}

