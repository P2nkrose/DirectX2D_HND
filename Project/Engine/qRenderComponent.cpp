#include "pch.h"
#include "qRenderComponent.h"

#include "qLevelMgr.h"
#include "qLevel.h"


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
	m_Mtrl = m_ShareMtrl = _Mtrl;
}

Ptr<qMaterial> qRenderComponent::GetSharedMtrl()
{
	m_Mtrl = m_ShareMtrl;
	return m_Mtrl;
}

Ptr<qMaterial> qRenderComponent::GetDynamicMaterial()
{
	// ���� ���� ���� �� ��ȯ�� ����(����) �� Play ����� ��쿡�� ȣ���� �Ǿ�� �Ѵ�.
	assert(qLevelMgr::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::PLAY);

	if (nullptr != m_DynamicMtrl)
		return m_Mtrl = m_DynamicMtrl;

	m_Mtrl = m_DynamicMtrl = m_ShareMtrl->Clone();

	return m_Mtrl;
}
