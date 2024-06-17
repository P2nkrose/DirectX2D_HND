#include "pch.h"
#include "qSprite.h"

qSprite::qSprite()
	: qAsset(ASSET_TYPE::SPRITE)
{
}

qSprite::~qSprite()
{
}

void qSprite::Create(Ptr<qTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel)
{
	m_Atlas = _Atlas;
	assert(m_Atlas);

	UINT width = m_Atlas->Width();
	UINT height = m_Atlas->Height();

	m_LeftTop = Vec2(_LeftTopPixel.x / (float)width, _LeftTopPixel.y / (float)height);
	m_Slice = Vec2(_SlicePixel.x / (float)width, _SlicePixel.y / (float)height);
}

void qSprite::SetBackground(Vec2 _Background)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_BackgroundUV = _Background / AtlasResolution;
}

void qSprite::SetOffset(Vec2 _Offset)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_OffsetUV = _Offset / AtlasResolution;
}
