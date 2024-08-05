#pragma once
#include "AE_Sub.h"
class AE_SpriteView : public AE_Sub
{
public:
	AE_SpriteView();
	~AE_SpriteView();

public:
	virtual void Init() override;
	virtual void Update() override;

	

};

