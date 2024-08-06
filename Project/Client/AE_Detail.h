#pragma once
#include "AE_Sub.h"

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
	void SpriteList();
	void AddAnimation();
	void DeleteAnimation();

public:
	void SetAnim(Ptr<qFlipBook> _FlipBook);
	string GetAnimName() { return m_AnimName; }


private:
	void SelectAnim(DWORD_PTR _ListUI);


private:
	vector<Ptr<qFlipBook>>		m_vecFlipBook;
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

