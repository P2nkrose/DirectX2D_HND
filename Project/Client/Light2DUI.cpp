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

	// 광원 종류
	LIGHT_TYPE	Type;

	// 광원 색상 정보

	// 광원의 반경 ( Point, Spot )
	float		Radius;

	// Spot 
	float		Angle;		// 광원 범위 각도
}
