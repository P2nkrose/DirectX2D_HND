#include "pch.h"
#include "qEditorMgr.h"

#include <Engine/components.h>
#include <Engine/qKeyMgr.h>
#include <Engine/qRenderMgr.h>
#include <Engine/qEngine.h>
#include <Engine/qDevice.h>

#include "qEditorCameraScript.h"
#include "qGameObjectEx.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include "EditorUI.h"


qEditorMgr::qEditorMgr()
{

}

qEditorMgr::~qEditorMgr()
{
	Delete_Vec(m_vecEditorObject);
	Delete_Map(m_mapUI);

	// ImGui Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void qEditorMgr::Init()
{
	CreateEditorObject();

	InitImGui();
}

void qEditorMgr::Tick()
{
	ShortCut();

	EditorObjectProgress();

	ImGuiProgress();
}


void qEditorMgr::ShortCut()
{
	if (KEY_TAP(KEY::I))
	{
		EditorUI* pUI = FindEditorUI("Inspector");

		if (pUI->IsActive())
			pUI->Deactivate();
		else
			pUI->Activate();
	}
}


void qEditorMgr::EditorObjectProgress()
{
	for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
	{
		m_vecEditorObject[i]->Tick();
	}

	for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
	{
		m_vecEditorObject[i]->FinalTick();
	}
}




void qEditorMgr::ImGuiTick()
{
	//ImGui::ShowDemoWindow();

	for (const auto& pair : m_mapUI)
	{
		pair.second->Tick();
	}
}



