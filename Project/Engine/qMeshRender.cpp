#include "pch.h"
#include "qMeshRender.h"

#include "qTransform.h"
#include "qFlipBookComponent.h"
#include "qSprite.h"

qMeshRender::qMeshRender()
	: qRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

qMeshRender::~qMeshRender()
{
}

void qMeshRender::FinalTick()
{
}

void qMeshRender::Render()
{
	if (!GetMesh() || !GetMaterial() || !GetMaterial()->GetShader())
		return;

	if (FlipBookComponent())
	{
		Ptr<qSprite> pCurSprite = FlipBookComponent()->GetCurSprite();

		pCurSprite->GetAtlasTexture()->Binding(10);
		GetMaterial()->SetScalarParam(VEC2_0, pCurSprite->GetLeftTopUV());
		GetMaterial()->SetScalarParam(VEC2_1, pCurSprite->GetSliceUV());
		GetMaterial()->SetScalarParam(INT_0, 1);
	}
	else
	{
		GetMaterial()->SetScalarParam(INT_0, 0);
	}

	Transform()->Binding();
	GetMaterial()->Binding();
	GetMesh()->render();
}
