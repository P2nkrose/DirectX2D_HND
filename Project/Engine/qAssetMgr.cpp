#include "pch.h"
#include "qAssetMgr.h"

#include "assets.h"

qAssetMgr::qAssetMgr()
{}

qAssetMgr::~qAssetMgr()
{

}

void qAssetMgr::Init()
{
	Ptr<qMesh> pMesh = nullptr;

	// RectMesh 생성
	// 0 --- 1
	// |  \  |
	// 3 --- 2


	// Vertex
	Vtx arrVtx[4] = {};

	arrVtx[0].vPos		= Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vColor	= Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[0].vUV		= Vec2(0.f, 0.f);

	arrVtx[1].vPos		= Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor	= Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[1].vUV		= Vec2(1.f, 0.f);

	arrVtx[2].vPos		= Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor	= Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV		= Vec2(1.f, 1.f);

	arrVtx[3].vPos		= Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor	= Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[3].vUV		= Vec2(0.f, 1.f);

	// Index 버퍼 생성
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;		arrIdx[1] = 1;		arrIdx[2] = 2;
	arrIdx[3] = 0;		arrIdx[4] = 2;		arrIdx[5] = 3;

	pMesh = new qMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh);

	// 쉐이더 생성
	Ptr<qGraphicShader> pShader = nullptr;
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_Test");
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_Test");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	AddAsset(L"TestShader", pShader);
}

Ptr<qAsset> qAssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<qAsset>>::iterator iter = m_mapAsset[(UINT)_Type].find(_Key);

	if (iter == m_mapAsset[(UINT)_Type].end())
	{
		return nullptr;
	}

	return iter->second;
}

Ptr<qTexture> qAssetMgr::CreateTexture(wstring _strKey, UINT _Width, UINT _Height
									 , DXGI_FORMAT _Format, UINT _Flags, D3D11_USAGE _Usage)
{
	// 중복 키 검사
	Ptr<qTexture> pTexture = FindAsset<qTexture>(_strKey);
	assert(!pTexture.Get());

	pTexture = new qTexture;
	if (FAILED(pTexture->Create(_Width, _Height, _Format, _Flags, _Usage)))
	{
		MessageBox(nullptr, L"텍스쳐 생성 실패", L"텍스쳐 생성 실패", MB_OK);
		return nullptr;
	}

	pTexture->m_Key = _strKey;
	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(_strKey, pTexture.Get()));

	return pTexture;
	
}

Ptr<qTexture> qAssetMgr::CreateTexture(wstring _strKey, ComPtr<ID3D11Texture2D> _Tex2D)
{
	// 중복키 검사
	Ptr<qTexture> pTexture = FindAsset<qTexture>(_strKey);
	assert(!pTexture.Get());

	pTexture = new qTexture;
	if (FAILED(pTexture->Create(_Tex2D)))
	{
		MessageBox(nullptr, L"텍스쳐 생성 실패", L"텍스쳐 생성 실패", MB_OK);
		return nullptr;
	}

	pTexture->m_Key = _strKey;
	m_mapAsset[(UINT)ASSET_TYPE::TEXTURE].insert(make_pair(_strKey, pTexture.Get()));

	return pTexture;
}
