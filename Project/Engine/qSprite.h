#pragma once
#include "qAsset.h"

class qSprite : public qAsset
{
public:
	qSprite();
	~qSprite();


public:
	void Create(Ptr<qTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel);

	virtual int Load(const wstring& _FilePath) { return S_OK; }
	virtual int Save(const wstring& _FilePath) { return S_OK; }
	
public:
	Ptr<qTexture> GetAtlasTexture() { return m_Atlas; }
	Vec2 GetLeftTopUV() { return m_LeftTop; }
	Vec2 GetSliceUV() { return m_Slice; }


private:
	Ptr<qTexture>		m_Atlas;
	Vec2				m_LeftTop;	// UV ÁÂÇ¥°è
	Vec2				m_Slice;	// UV ÁÂÇ¥°è
};

