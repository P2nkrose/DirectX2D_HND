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
	m_FinalPos = Transform()->GetRelativePos() + m_Offset;
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
