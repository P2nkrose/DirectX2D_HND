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

	// RectMesh 积己
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

	// Index 滚欺 积己
	UINT arrIdx[6] = {};
	arrIdx[0] = 0;		arrIdx[1] = 1;		arrIdx[2] = 2;
	arrIdx[3] = 0;		arrIdx[4] = 2;		arrIdx[5] = 3;

	pMesh = new qMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh);

	// 溅捞歹 积己
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
