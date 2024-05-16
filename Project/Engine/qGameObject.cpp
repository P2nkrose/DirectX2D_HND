#include "pch.h"
#include "qGameObject.h"

#include "qTimeMgr.h"
#include "qKeyMgr.h"

#include "qTransform.h"
#include "qComponent.h"
#include "qRenderComponent.h"

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
}

void qGameObject::Tick()
{
	float dt = qTimeMgr::GetInst()->GetDeltaTime();

	Vec3 vPos = Transform()->GetRelativePos();

	if (qKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::PRESSED)
	{
		vPos.x -= dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::PRESSED)
	{
		vPos.x += dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::PRESSED)
	{
		vPos.y += dt * 1.f;
	}

	if (qKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::PRESSED)
	{
		vPos.y -= dt * 1.f;
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

