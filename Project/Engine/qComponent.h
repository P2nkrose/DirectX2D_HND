#pragma once
#include "qEntity.h"
#include "qGameObject.h"

#define GET_OTHER_COMPONENT(Type) q##Type* Type() { return m_Owner->Type(); }

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

	GET_OTHER_COMPONENT(Transform);
	GET_OTHER_COMPONENT(MeshRender);
	GET_OTHER_COMPONENT(Camera);
	GET_OTHER_COMPONENT(Collider2D);
	GET_OTHER_COMPONENT(FlipBookComponent);
	GET_OTHER_COMPONENT(TileMap);
	GET_OTHER_COMPONENT(Light2D);
	

private:
	void SetOwner(qGameObject* _Object) { m_Owner = _Object; }


private:
	const COMPONENT_TYPE	m_Type;
	qGameObject*			m_Owner;
};

