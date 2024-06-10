#pragma once
#include "qAsset.h"

class qSprite;

class qFilpBook : public qAsset
{
public:
	qFilpBook();
	~qFilpBook();

public:
	void FinalTick();

private:
	vector<qSprite*>	m_vecSprite;
};

