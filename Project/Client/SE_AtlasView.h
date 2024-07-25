#pragma once
#include "SE_Sub.h"

class SE_AtlasView : public SE_Sub
{
public:
	SE_AtlasView();
	~SE_AtlasView();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetAtlasTex(Ptr<qTexture> _Tex);

private:
	void WheelCheck();
	void SelectCheck();
	void DrawSelectRect();


private:
	Ptr<qTexture>		m_AtlasTex;

	ImVec2				ImageRectMin;		// Image ���� �»�� ���� ��ġ
	ImVec2				m_MousePos;			// ���� ���콺 ��ġ

	ImVec2				m_MouseLT;			// ���콺 ��ġ�� �ش��ϴ� Texture�� �ȼ� ��ǥ Left Top
	ImVec2				m_MouseRB;			// ���콺 ��ġ�� �ش��ϴ� Texture�� �ȼ� ��ǥ Right Bottom


	float				m_WidthSize;
	float				m_WheelScale;
	float				m_Ratio;		// ���� �ػ� ��� ��� �̹����� ����
};

