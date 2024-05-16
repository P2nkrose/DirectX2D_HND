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
	m_matWorld.Translation();	// ������Ŀ��� 4�� 1, 2, 3 �� ��ȯ, �̵���

	// GPU �� ��� �����͸� �����ϴ� �������� �߻��ϴ� ��ġ�� �̸� �����ؼ� ��ġ�� �ϰų�
	// HLSL ���� ��� ������ ������ �� row_major �� �ٿ��־�� �Ѵ�.
	//m_matWorld = XMMatrixTranspose(m_matWorld);

	//tTransform trans = {};
	//trans.Pos = m_RelativePos;
	//trans.Scale = m_RelativeScale;

	//qConstBuffer* pTransformCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	//pTransformCB->SetData(&trans);
	//pTransformCB->Binding();
}
