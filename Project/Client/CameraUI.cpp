#include "pch.h"
#include "CameraUI.h"

CameraUI::CameraUI()
	: ComponentUI(COMPONENT_TYPE::CAMERA)
{
}

CameraUI::~CameraUI()
{
}

void CameraUI::Update()
{
	Title();
}

void CameraUI::LayerCheck()
{
}
