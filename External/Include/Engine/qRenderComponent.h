#pragma once
#include "qComponent.h"

class qRenderComponent : public qComponent
{
public:
	qRenderComponent(COMPONENT_TYPE _Type);
	~qRenderComponent();

public:
	virtual void FinalTick() PURE;
	virtual void Render() PURE;
	virtual qRenderComponent* Clone() PURE;

public:
	void SetMesh(Ptr<qMesh> _Mesh) { m_Mesh = _Mesh; }
	void SetMaterial(Ptr<qMaterial> _Mtrl) { m_Mtrl = _Mtrl; }

	Ptr<qMesh> GetMesh() { return m_Mesh; }
	Ptr<qMaterial> GetMaterial() { return m_Mtrl; }


private:
	Ptr<qMesh>					m_Mesh;
	Ptr<qMaterial>				m_Mtrl;
};

	