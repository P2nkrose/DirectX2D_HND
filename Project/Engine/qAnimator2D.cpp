#include "pch.h"
#include "qAnimator2D.h"

qAnimator2D::qAnimator2D()
	: qComponent(COMPONENT_TYPE::ANIMATOR2D)
{
}

qAnimator2D::~qAnimator2D()
{
}

void qAnimator2D::FinalTick()
{
	if (m_CurAnim)
	{
		//m_CurAnim->FinalTick();
	}
}
