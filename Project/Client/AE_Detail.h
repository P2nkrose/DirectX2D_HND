#pragma once
#include "AE_Sub.h"

#include "ListUI.h"

class AE_Detail : public AE_Sub
{
public:
	friend class AE_Preivew;
	friend class AE_SpriteView;

	AE_Detail();
	~AE_Detail();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void Animation();
	void AnimInfo();
	void SpriteList();
	void AddAnimation();
	void DeleteAnimation();

public:
	void SetAnim(Ptr<qFlipBook> _FlipBook);
	string GetAnimName() { return m_AnimName; }

public:
	void AddSprite(Ptr<qSprite> _Sprite) { m_vecSprite.push_back(_Sprite); }
	Ptr<qSprite> GetSprite(int _Idx) { return m_vecSprite[_Idx]; }



private:
	void SelectAnim(DWORD_PTR _ListUI);

private:
	ListUI*						m_List;

	vector<Ptr<qFlipBook>>		m_vecFlipBook;
	vector<Ptr<qSprite>>		m_vecSprite;
	Ptr<qFlipBook>				m_CurFlipBook;
	Ptr<qSprite>				m_CurFrmSprite;

	string						m_AnimName;

	int							m_CurFrmIdx;
	int							m_MaxFrm;
	float						m_FPS;
	float						m_AccTime;
	bool						m_Repeat;
	bool						m_Finish;
	
	

};

