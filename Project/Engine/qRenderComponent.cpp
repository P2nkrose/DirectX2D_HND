#include "pch.h"
#include "qRenderComponent.h"

qRenderComponent::qRenderComponent(COMPONENT_TYPE _Type)
	: qComponent(_Type)
	, m_Mesh(nullptr)
	, m_Mtrl(nullptr)
{
}

qRenderComponent::~qRenderComponent()
{
}
