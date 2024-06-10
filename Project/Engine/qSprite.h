#pragma once
#include "qAsset.h"

class qSprite : public qAsset
{
public:
	qSprite();
	~qSprite();


public:
	void Create(Ptr<qTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel);


private:
	Ptr<qTexture>		m_Atlas;
	Vec2				m_LeftTop;	// UV ÁÂÇ¥°è
	Vec2				m_Slice;	// UV ÁÂÇ¥°è
};

