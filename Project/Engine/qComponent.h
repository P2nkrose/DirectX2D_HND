#pragma once
#include "qEntity.h"
#include "qGameObject.h"


class qComponent : public qEntity
{
public:
	friend class qGameObject;

	virtual qComponent* Clone() = 0;
	qComponent(COMPONENT_TYPE _Type);
	~qComponent();

	virtual void Begin();
	virtual void Tick();
	virtual void FinalTick() = 0;

public:
	COMPONENT_TYPE GetComponentType() { return m_Type; }
	qGameObject* GetOwner() { return m_Owner; }


private:
	void SetOwner(qGameObject* _Object) { m_Owner = _Object; }


private:
	const COMPONENT_TYPE	m_Type;
	qGameObject*			m_Owner;
};

