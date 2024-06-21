#include "pch.h"
#include "TransformUI.h"

#include <Engine/qGameObject.h>
#include <Engine/qTransform.h>

TransformUI::TransformUI()
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::Update()
{
	if (nullptr == GetTargetObject())
		return;

	// ===============
	//    Transform
	// ===============

	qTransform* pTrans = GetTargetObject()->Transform();

	Vec3 vPos = pTrans->GetRelativePos();
	Vec3 vScale = pTrans->GetRelativeScale();
	Vec3 vRot = pTrans->GetRelativeRotation();

	ImGui::Text("Position");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Pos", vPos);

	ImGui::Text("Scale");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Scale", vScale);

	ImGui::Text("Rotation");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Rot", vRot, 0.01f);

	pTrans->SetRelativePos(vPos);
	pTrans->SetRelativeScale(vScale);
	pTrans->SetRelativeRotation(vRot);

	// Independent Scale

}
