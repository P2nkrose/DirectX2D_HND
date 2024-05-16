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
	void SetShader(Ptr<qGraphicShader> _Shader) { m_Shader = _Shader; }

	Ptr<qMesh> GetMesh() { return m_Mesh; }
	Ptr<qGraphicShader> GetShader() { return m_Shader; }


private:
	Ptr<qMesh>					m_Mesh;
	Ptr<qGraphicShader>			m_Shader;
};

	