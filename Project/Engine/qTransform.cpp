#include "pch.h"
#include "qTransform.h"

#include "qDevice.h"
#include "qConstBuffer.h"

qTransform::qTransform()
	: qComponent(COMPONENT_TYPE::TRANSFORM)
{
}

qTransform::~qTransform()
{
}

void qTransform::FinalTick()
{
}

void qTransform::Binding()
{
	m_matWorld = XMMatrixIdentity();
	m_matWorld.Translation();	// 상태행렬에서 4행 1, 2, 3 열 반환, 이동값

	// GPU 에 행렬 데이터를 전달하는 과정에서 발생하는 전치를 미리 예상해서 전치를 하거나
	// HLSL 에서 행렬 변수를 선언할 때 row_major 를 붙여주어야 한다.
	//m_matWorld = XMMatrixTranspose(m_matWorld);

	//tTransform trans = {};
	//trans.Pos = m_RelativePos;
	//trans.Scale = m_RelativeScale;

	//qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	//pTransformCB->SetData(&trans);
	//pTransformCB->Binding();
}
