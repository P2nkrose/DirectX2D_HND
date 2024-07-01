#include "pch.h"
#include "qRenderComponent.h"

#include "qLevelMgr.h"


qRenderComponent::qRenderComponent(COMPONENT_TYPE _Type)
	: qComponent(_Type)
	, m_Mesh(nullptr)
	, m_Mtrl(nullptr)
{
}

qRenderComponent::~qRenderComponent()
{
}

void qRenderComponent::SetMaterial(Ptr<qMaterial> _Mtrl)
{
	m_Mtrl = _Mtrl;
}

Ptr<qMaterial> qRenderComponent::GetSharedMtrl()
{
	return Ptr<qMaterial>();
}

Ptr<qMaterial> qRenderComponent::GetDynamicMaterial()
{
	return Ptr<qMaterial>();
}
