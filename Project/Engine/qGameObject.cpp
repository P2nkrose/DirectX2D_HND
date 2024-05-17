#include "pch.h"
#include "qGameObject.h"

#include "qTimeMgr.h"
#include "qKeyMgr.h"

#include "components.h"

qGameObject::qGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
{
}

qGameObject::~qGameObject()
{
	Delete_Array(m_arrCom);
}


void qGameObject::AddComponent(qComponent* _Component)
{
	COMPONENT_TYPE Type = _Component->GetComponentType();

	assert(nullptr == m_arrCom[(UINT)Type]);

	m_arrCom[(UINT)Type] = _Component;
	m_arrCom[(UINT)Type]->SetOwner(this);

	qRenderComponent* pRenderCom = dynamic_cast<qRenderComponent*>(_Component);

	assert(!(pRenderCom && m_RenderCom));

	if (pRenderCom)
		m_RenderCom = pRenderCom;
}



void qGameObject::Begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->Begin();
	}
}

void qGameObject::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= DT * 1.f;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += DT * 1.f;
	}

	if (KEY_PRESSED(KEY::UP))
	{
		vPos.y += DT * 1.f;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		vPos.y -= DT * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::Z) == KEY_STATE::PRESSED)
	{
		Vec3 vRot = Transform()->GetRelativeRotation();

		vRot.z += DT * XM_PI * 2.f;

		Transform()->SetRelativeRotation(vRot);
	}


	Transform()->SetRelativePos(vPos);
}

void qGameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->FinalTick();
	}
}

void qGameObject::Render()
{
	if (m_RenderCom)
		m_RenderCom->Render();
}

