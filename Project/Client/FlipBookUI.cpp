#include "pch.h"
#include "FlipBookUI.h"

#include <Engine/qFlipBook.h>

FlipBookUI::FlipBookUI()
	: AssetUI(ASSET_TYPE::FLIPBOOK)
{
}

FlipBookUI::~FlipBookUI()
{
}

void FlipBookUI::Update()
{
	Title();

	Ptr<qFlipBook> pFlipBook = (qFlipBook*)GetAsset().Get();

	// ¿ÃπÃ¡ˆ

}
