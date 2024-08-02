#pragma once
#include "EditorUI.h"

class AE_Detail;
class AE_Preview;
class AE_SpriteView;

class AnimationEditor : public EditorUI
{
public:
	AnimationEditor();
	~AnimationEditor();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	virtual void Activate() override;
	virtual void Deactivate() override;

public:
	AE_Preview* GetPreview() { return m_Preview; }
	AE_SpriteView* GetSpriteView() { return m_SpriteView; }
	AE_Detail* GetDetail() { return m_Detail; }

	
private:
	void AddAnimation();
	void DeleteAnimation(const wstring& _strAnimationName);


private:
	AE_Preview*			m_Preview;
	AE_SpriteView*		m_SpriteView;
	AE_Detail*			m_Detail;


};

