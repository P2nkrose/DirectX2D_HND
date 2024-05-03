#include "pch.h"
#include "Temp.h"

#include "qDevice.h"

// Vertex Buffer 버텍스 버퍼
ID3D11Buffer* g_VB = nullptr;
Vtx g_Vtx[3] = {};

// Vertex Shader 버텍스 쉐이더
ID3D11VertexShader* g_VS = nullptr;

// Pixel Shader  픽셀 쉐이더
ID3D11PixelShader* g_PS = nullptr;

int TempInit()
{
	// 버텍스 버퍼 생성
	g_Vtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_Vtx[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	g_Vtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_Vtx[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	g_Vtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_Vtx[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);


	D3D11_BUFFER_DESC tVtxBufferDesc = {};

	tVtxBufferDesc.ByteWidth = sizeof(Vtx) * 3;				// 버텍스버퍼데스크의 크기
	tVtxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 버텍스버퍼의 용도
	tVtxBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tVtxBufferDesc.CPUAccessFlags = 0;
	tVtxBufferDesc.MiscFlags = 0;
	tVtxBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_Vtx;

	if (FAILED(DEVICE->CreateBuffer(&tVtxBufferDesc, &tSub, &g_VB)))
	{
		MessageBox(nullptr, L"VertexBuffer 생성 실패", L"Temp 초기화 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void TempTick()
{
}

void TempRender()
{
}

void TempRelease()
{
	if (nullptr != g_VB)
		g_VB->Release();
}
