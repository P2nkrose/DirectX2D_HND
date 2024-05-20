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
	// 오브젝트의 월드행렬 계산
	// 크기 행렬
	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z);

	// 이동 행렬
	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);

	// 회전 행렬
	Matrix matRot = XMMatrixRotationX(m_RelativeRotation.x)
				  * XMMatrixRotationY(m_RelativeRotation.y)
				  * XMMatrixRotationZ(m_RelativeRotation.z);

	m_matWorld = matScale * matRot * matTranslation;


	// 방향 벡터 계산
	m_RelativeDir[DIR::RIGHT]	= Vec3(1.f, 0.f, 0.f);
	m_RelativeDir[DIR::UP]		= Vec3(0.f, 1.f, 0.f);
	m_RelativeDir[DIR::FRONT]	= Vec3(0.f, 0.f, 1.f);

	// HLSL mul (방향벡터 곱해주기)
	// w 를 1 로 확장
	//XMVector3TransformCoord(m_RelativeDir[DIR::RIGHT], matRot);

	// w 를 0으로 확장
	for (int i = 0; i < 3; ++i)
	{
		m_RelativeDir[i] = XMVector3TransformNormal(m_RelativeDir[i], matRot);
		m_RelativeDir[i].Normalize();
	}

}

void qTransform::Binding()
{
	// GPU 에 행렬 데이터를 전달하는 과정에서 발생하는 전치를 미리 예상해서 전치를 하거나
	// HLSL 에서 행렬 변수를 선언할 때 row_major 를 붙여주어야 한다.
	
	g_Trans.matWorld = m_matWorld;

	qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	pTransformCB->SetData(&g_Trans);
	pTransformCB->Binding();
}
