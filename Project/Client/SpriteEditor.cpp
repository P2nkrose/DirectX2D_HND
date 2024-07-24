#include "pch.h"
#include "SpriteEditor.h"

#include "qEditorMgr.h"
#include "SE_AtlasView.h"
#include "SE_Detail.h"

SpriteEditor::SpriteEditor()
{
}

SpriteEditor::~SpriteEditor()
{
}

void SpriteEditor::Init()
{
	m_AtlasView = (SE_AtlasView*)qEditorMgr::GetInst()->FindEditorUI("SE_AtlasView");
	m_Detail = (SE_Detail*)qEditorMgr::GetInst()->FindEditorUI("SE_Detail");
}

void SpriteEditor::Update()
{
}
