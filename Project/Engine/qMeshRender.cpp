#include "pch.h"
#include "qMeshRender.h"

#include "qTransform.h"

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

	Transform()->Binding();
	GetMaterial()->Binding();
	GetMesh()->render();
}
