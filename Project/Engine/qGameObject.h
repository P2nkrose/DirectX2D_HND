#pragma once
#include "pch.h"
#include "qEntity.h"

class qComponent;
class qRenderComponent;
class qScript;

#define GET_COMPONENT(Type, TYPE) class q##Type* Type() { return (q##Type*)GetComponent(COMPONENT_TYPE::TYPE); }


class qGameObject : public qEntity
{
public:

	friend class qLevel;
	friend class qLayer;

	CLONE(qGameObject);
	qGameObject();
	~qGameObject();

	void Begin();
	void Tick();
	void FinalTick();
	void Render();

public:
	void AddComponent(qComponent* _Component);
	qComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
	qRenderComponent* GetRenderComponent() { return m_RenderCom; }

	qGameObject* GetParent() { return m_Parent; }
	int GetLayerIdx() { return m_LayerIdx; }
	
public:
	void AddChild(qGameObject* _ChildObject);
	const vector<qGameObject*>& GetChildren() { return m_vecChildren; }

	void DisconnectWithLayer();


	GET_COMPONENT(Transform, TRANSFORM);
	GET_COMPONENT(MeshRender, MESHRENDER);
	GET_COMPONENT(Camera, CAMERA);


private:
	qComponent*				m_arrCom[(UINT)COMPONENT_TYPE::END];
	qRenderComponent*		m_RenderCom;
	vector<qScript*>		m_vecScript;

	qGameObject*			m_Parent;
	vector<qGameObject*>	m_vecChildren;

	int						m_LayerIdx;		// 소속 레이어의 인덱스 번호
};

