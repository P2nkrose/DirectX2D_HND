#pragma once
#include "SE_Sub.h"

class SE_Detail : public SE_Sub
{
public:
	SE_Detail();
	~SE_Detail();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetAtlasTex(Ptr<qTexture> _Tex);
	string GetSpriteName() { return m_SpriteName; }


private:
	void SelectTexture(DWORD_PTR _ListUI);

private:
	void Atlas();
	void AtlasInfo();
	void SpriteInfo();
	void CreateSprite();

private:
	Ptr<qTexture>		m_AtlasTex;

	string             m_SpriteName;

	ImVec2				ImageRectMin;		// Image ���� �»�� ���� ��ġ

	ImVec2				m_MousePos;			// ���� ���콺 ��ġ

	ImVec2				m_MouseLT;			// ���콺 ��ġ�� �ش��ϴ� Texture�� �ȼ� ��ǥ Left Top
	ImVec2				m_MouseRB;			// ���콺 ��ġ�� �ش��ϴ� Texture�� �ȼ� ��ǥ Right Bottom

	ImVec2				LeftTop;
	ImVec2				RightBottom;
};

