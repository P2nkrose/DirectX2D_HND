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
	void SetMesh(qMesh* _Mesh) { m_Mesh = _Mesh; }
	void SetShader(qGraphicShader* _Shader) { m_Shader = _Shader; }

	qMesh* GetMesh() { return m_Mesh; }
	qGraphicShader* GetShader() { return m_Shader; }


private:
	qMesh*					m_Mesh;
	qGraphicShader*			m_Shader;
};

	