#pragma once
#include "ComponentUI.h"

class FlipBookComUI : public ComponentUI
{
public:
	FlipBookComUI();
	~FlipBookComUI();

private:
	virtual void Update() override;
};

