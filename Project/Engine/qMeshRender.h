#pragma once
#include "qRenderComponent.h"

class qMeshRender : public qRenderComponent
{
public:
	CLONE(qMeshRender);
	qMeshRender();
	~qMeshRender();

public:
	virtual void FinalTick() override;
	virtual void Render() override;

};

