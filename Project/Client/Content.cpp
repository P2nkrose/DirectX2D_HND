#include "pch.h"
#include "Content.h"

Content::Content()
{
}

Content::~Content()
{
}

void Content::Update()
{
	Vec4 vData;
	ImGui::DragFloat4("data", vData);
}
