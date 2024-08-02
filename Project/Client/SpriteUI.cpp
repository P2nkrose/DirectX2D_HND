#include "pch.h"
#include "SpriteUI.h"

#include <Engine/qTexture.h>

SpriteUI::SpriteUI()
	: AssetUI(ASSET_TYPE::SPRITE)
{
}

SpriteUI::~SpriteUI()
{
}

void SpriteUI::Update()
{
	Title();

	ImGui::Text("");

	Sprite();
}

void SpriteUI::Sprite()
{
	// 스프라이트 이름
	OutputAssetName();

	ImGui::Text("");
	ImGui::Text("                     ");
	ImGui::SameLine();

	Ptr<qSprite> pTexture = (qSprite*)GetAsset().Get();

	ImVec2 LTUV = ImVec2(pTexture->GetLeftTopUV().x, pTexture->GetLeftTopUV().y);
	ImVec2 Slice = ImVec2(pTexture->GetSliceUV().x, pTexture->GetSliceUV().y);
	ImVec2 Resolution = ImVec2(pTexture->GetAtlasTexture()->Width(), pTexture->GetAtlasTexture()->Height());

	ImVec2 LTSize = ImVec2(Resolution.x * LTUV.x, Resolution.y * LTUV.y);
	ImVec2 SliceSize = ImVec2(Resolution.x * Slice.x, Resolution.y * Slice.y);
	ImVec2 RBSize = ImVec2(LTSize.x + SliceSize.x, LTSize.y + SliceSize.y);

	ImVec2 RBUV = ImVec2(RBSize.x / Resolution.x, RBSize.y / Resolution.y);

	ImVec2 OffsetUV = ImVec2(pTexture->GetOffsetUV().x, pTexture->GetOffsetUV().y);
	ImVec2 BGUV = ImVec2(pTexture->GetBackgroundUV().x, pTexture->GetBackgroundUV().y);

	ImVec2 BGSize = ImVec2(Resolution.x * BGUV.x, Resolution.y * BGUV.y);

	ImVec4 tint_col = ImVec4(1.f, 1.f, 1.f, 1.f);
	ImVec4 border_col = ImVec4(0.7f, 0.7f, 0.7f, 1.f);

	ImGui::Image(pTexture->GetAtlasTexture()->GetSRV().Get(), ImVec2(150, 150), LTUV, RBUV, tint_col, border_col);

	ImGui::Text("");
	ImGui::Separator();
	ImGui::Text("");

	ImGui::Text("Left Top");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300.f);
	ImGui::InputFloat2("##LeftTop", (float*)&LTSize);
	
	ImGui::Text("Slice");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300.f);
	ImGui::InputFloat2("##Slice", (float*)&SliceSize);

	ImGui::Text("Offset");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300.f);
	ImGui::InputFloat2("##Offset", (float*)&OffsetUV);

	ImGui::Text("BackGround");
	ImGui::SameLine(105);
	ImGui::SetNextItemWidth(300);
	ImGui::InputFloat2("##BackGround", (float*)&BGSize);

}


