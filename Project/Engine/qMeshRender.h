#pragma once
#include "qRenderComponent.h"

class qMeshRender : public qRenderComponent
{
public:
	qMeshRender();
	~qMeshRender();

public:
	virtual void FinalTick() override;
	virtual void Render() override;

	virtual qMeshRender* Clone() { return new qMeshRender(*this); }
};

