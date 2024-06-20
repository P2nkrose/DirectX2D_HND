#pragma once

#include "ImGui/imgui.h"

class EditorUI
{
public:
	EditorUI();
	~EditorUI();

public:
	virtual void Tick();
	virtual void Update() PURE;

	
public:
	void SetName(const string& _Name) { m_Name = _Name; }
	const string& GetName() { return m_Name; }
	
	bool IsActive() { return m_Active; }
	void Activate() { m_Active = true; }
	void Deactivate() { m_Active = false; }


private:
	string		m_Name;
	bool		m_Active;


};

