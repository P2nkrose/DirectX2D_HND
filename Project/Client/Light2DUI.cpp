#include "pch.h"
#include "Light2DUI.h"

Light2DUI::Light2DUI()
	: ComponentUI(COMPONENT_TYPE::LIGHT2D)
{
}

Light2DUI::~Light2DUI()
{
}

void Light2DUI::Update()
{
	Title();

	// ���� ����
	LIGHT_TYPE	Type;

	// ���� ���� ����

	// ������ �ݰ� ( Point, Spot )
	float		Radius;

	// Spot 
	float		Angle;		// ���� ���� ����
}
