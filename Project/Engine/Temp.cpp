#include "pch.h"
#include "Temp.h"

#include "qDevice.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"

#include "qEntity.h"
#include "qMesh.h"
#include "qConstBuffer.h"
#include "qGraphicShader.h"

tTransform g_ObjTrans = {};
qMesh* g_Mesh = nullptr;
qGraphicShader* g_Shader = nullptr;


int TempInit()
{
	g_ObjTrans.Scale = Vec4(1.2f, 1.2f, 1.2f, 1.f);

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

	g_Mesh = new qMesh;
	g_Mesh->Create(arrVtx, 4, arrIdx, 6);

	// 溅捞歹 积己
	g_Shader = new qGraphicShader;
	g_Shader->CreateVertexShader(L"shader\\test.fx", "VS_Test");
	g_Shader->CreatePixelShader(L"shader\\test.fx", "PS_Test");

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

	qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->SetData(&g_ObjTrans);
}

void TempRender()
{
	qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->Binding();

	g_Shader->Binding();

	g_Mesh->render();
}

void TempRelease()
{
	delete g_Mesh;
	delete g_Shader;
}

