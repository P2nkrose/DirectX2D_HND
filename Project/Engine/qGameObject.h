#pragma once
#include "qEntity.h"

class qComponent;
class qRenderComponent;

#define GET_COMPONENT(Type, TYPE) class q##Type* Type() { return (q##Type*)GetComponent(COMPONENT_TYPE::TYPE); }


class qGameObject : public qEntity
{
public:
	virtual qGameObject* Clone() { return new qGameObject(*this); }
	qGameObject();
	~qGameObject();

	void Begin();
	void Tick();
	void FinalTick();
	void Render();

public:
	void AddComponent(qComponent* _Component);
	qComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

	GET_COMPONENT(Transform, TRANSFORM);
	GET_COMPONENT(MeshRender, MESHRENDER);
	GET_COMPONENT(Camera, CAMERA);


private:
	qComponent*			m_arrCom[(UINT)COMPONENT_TYPE::END];
	qRenderComponent*	m_RenderCom;
};

