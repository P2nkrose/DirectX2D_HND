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
	// ������Ʈ�� ������� ���
	// ũ�� ���
	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z);

	// �̵� ���
	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);

	// ȸ�� ���
	Matrix matRot = XMMatrixRotationX(m_RelativeRotation.x)
				  * XMMatrixRotationY(m_RelativeRotation.y)
				  * XMMatrixRotationZ(m_RelativeRotation.z);

	m_matWorld = matScale * matRot * matTranslation;


	// ���� ���� ���
	m_RelativeDir[DIR::RIGHT]	= Vec3(1.f, 0.f, 0.f);
	m_RelativeDir[DIR::UP]		= Vec3(0.f, 1.f, 0.f);
	m_RelativeDir[DIR::FRONT]	= Vec3(0.f, 0.f, 1.f);

	// HLSL mul (���⺤�� �����ֱ�)
	// w �� 1 �� Ȯ��
	//XMVector3TransformCoord(m_RelativeDir[DIR::RIGHT], matRot);

	// w �� 0���� Ȯ��
	for (int i = 0; i < 3; ++i)
	{
		m_RelativeDir[i] = XMVector3TransformNormal(m_RelativeDir[i], matRot);
		m_RelativeDir[i].Normalize();
	}

}

void qTransform::Binding()
{
	// GPU �� ��� �����͸� �����ϴ� �������� �߻��ϴ� ��ġ�� �̸� �����ؼ� ��ġ�� �ϰų�
	// HLSL ���� ��� ������ ������ �� row_major �� �ٿ��־�� �Ѵ�.
	
	g_Trans.matWorld = m_matWorld;

	qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	pTransformCB->SetData(&g_Trans);
	pTransformCB->Binding();
}
