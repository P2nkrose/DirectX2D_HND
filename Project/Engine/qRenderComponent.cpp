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
	// 동적 재질 생성 및 반환은 게임(레벨) 이 Play 모드인 경우에만 호출이 되어야 한다.
	assert(qLevelMgr::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::PLAY);

	if (nullptr != m_DynamicMtrl)
		return m_Mtrl = m_DynamicMtrl;

	m_Mtrl = m_DynamicMtrl = m_ShareMtrl->Clone();

	return m_Mtrl;
}
