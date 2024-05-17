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
}

void qTransform::Binding()
{
	// GPU �� ��� �����͸� �����ϴ� �������� �߻��ϴ� ��ġ�� �̸� �����ؼ� ��ġ�� �ϰų�
	// HLSL ���� ��� ������ ������ �� row_major �� �ٿ��־�� �Ѵ�.
	
	tTransform trans = {};
	trans.matWorld = m_matWorld;

	qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	pTransformCB->SetData(&trans);
	pTransformCB->Binding();
}
