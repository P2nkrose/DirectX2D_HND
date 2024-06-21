#pragma once

#include "ImGui/imgui.h"

class EditorUI
{
public:
	EditorUI();
	~EditorUI();

public:
	virtual void Tick();
	virtual void Update() PURE;			// 자식이 override받아서 쓰는 고유의 Tick

	
public:
	bool IsActive() { return m_Active; }
	void Activate() { m_Active = true; }
	void Deactivate() { m_Active = false; }


public:
	void AddChild(EditorUI* _UI);

	EditorUI* GetParent() { return m_Parent; }
	const vector<EditorUI*>& GetChildren() { return m_vecChildUI; }

	void SetName(const string& _Name);
	const string& GetName() { return m_Name; }

	UINT GetID() { return m_ID; }
	const string& GetFullName() { return m_FullName; }

	void SetChildBorder(bool _Set) { m_ChildBorder = _Set; }
	void SetChildSize(ImVec2 _Size) { m_ChildSize = _Size; }

private:
	static UINT			m_GlobalID;

	string				m_Name;
	string				m_FullName;
	const UINT			m_ID;
	bool				m_Active;

	EditorUI*			m_Parent;
	vector<EditorUI*>	m_vecChildUI;

	ImVec2				m_ChildSize;

	bool				m_ChildBorder;

};

