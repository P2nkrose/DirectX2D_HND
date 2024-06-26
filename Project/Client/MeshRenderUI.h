#pragma once
#include "ComponentUI.h"

class MeshRenderUI : public ComponentUI
{
public:
	MeshRenderUI();
	~MeshRenderUI();

private:
	virtual void Update() override;
};

