#pragma once
#include "qAsset.h"

class qSprite;

class qFlipBook : public qAsset
{
public:
	qFlipBook();
	~qFlipBook();

public:
	void FinalTick();

private:
	vector<qSprite*>	m_vecSprite;
};

