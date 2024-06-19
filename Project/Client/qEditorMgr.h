#pragma once

#include <Engine/singleton.h>

class qGameObject;

class qEditorMgr : public qSingleton<qEditorMgr>
{
	SINGLE(qEditorMgr);

public:
	void Init();
	void Tick();

private:
	void CreateEditorObject();

	void InitImGui();
	void ImGuiProgress();
	void ImGuiTick();


private:
	vector<qGameObject*>	m_vecEditorObject;
};

