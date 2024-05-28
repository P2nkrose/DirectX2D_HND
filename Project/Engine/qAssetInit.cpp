#include "pch.h"
#include "qAssetMgr.h"

void qAssetMgr::Init()
{
	CreateEngineMesh();

	CreateEngineTexture();

	CreateEngineGraphicShader();

	CreateEngineComputeShader();

	CreateEngineMaterial();
}

void qAssetMgr::CreateEngineMesh()
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
	arrVtx[0].vUV = Vec2(0.f, 0.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);

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

void qAssetMgr::CreateEngineTexture()
{
}

void qAssetMgr::CreateEngineGraphicShader()
{
	Ptr<qGraphicShader> pShader = nullptr;

	// Std2DShader
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_MASKED);

	AddAsset(L"Std2DShader", pShader);


	// Std2DAlphaBlend
	pShader = new qGraphicShader;
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);

	pShader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);

	AddAsset(L"Std2DAlphaBlendShader", pShader);

}

void qAssetMgr::CreateEngineComputeShader()
{
}

void qAssetMgr::CreateEngineMaterial()
{
	Ptr<qMaterial> pMtrl = nullptr;

	// Std2DMtrl
	pMtrl = new qMaterial();
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DShader"));
	AddAsset(L"Std2DMtrl", pMtrl);


	// Std2DAlphaBlendMtrl
	pMtrl = new qMaterial();
	pMtrl->SetShader(FindAsset<qGraphicShader>(L"Std2DAlphaBlendShader"));
	AddAsset(L"Std2DAlphaBlendMtrl", pMtrl);
}
