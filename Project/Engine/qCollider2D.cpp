#include "pch.h"
#include "qCollider2D.h"

#include "qTransform.h"


qCollider2D::qCollider2D()
	: qComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_OverlapCount(0)
{
}

qCollider2D::~qCollider2D()
{
}

void qCollider2D::FinalTick()
{
	Matrix matTranslation = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);
	Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	// 크기, 회전, 이동
	Matrix matObjectScaleInv = XMMatrixIdentity();

	if (m_IndependentScale)
	{
		Vec3 vObjectScale = GetOwner()->Transform()->GetWorldScale();
		matObjectScaleInv = XMMatrixScaling(vObjectScale.x, vObjectScale.y, vObjectScale.z);
		matObjectScaleInv = XMMatrixInverse(nullptr, matObjectScaleInv);
	}

	m_matColWorld = matScale * matTranslation * matObjectScaleInv * GetOwner()->Transform()->GetWorldMat();

	// Debug 렌더링으로 충돌체의 위치를 표시
	DrawDebugRect(m_matColWorld, Vec4(0.f, 1.f, 0.f, 1.f), 0.f, false);
}

void qCollider2D::BeginOverlap(qCollider2D* _Other)
{
}

void qCollider2D::Overlap(qCollider2D* _Other)
{
}

void qCollider2D::EndOverlap(qCollider2D* _Other)
{
}
