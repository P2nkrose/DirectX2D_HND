#pragma once
#include "qAsset.h"

#include "qSprite.h"

class qFlipBook : public qAsset
{
public:
	qFlipBook();
	~qFlipBook();

public:
	void FinalTick();

	virtual int Load(const wstring& _FilePath) override;
	virtual int Save(const wstring& _FilePath) override;


public:
	void AddSprite(Ptr<qSprite> _Sprite) { m_vecSprite.push_back(_Sprite); }
	Ptr<qSprite> GetSprite(int _Idx) { return m_vecSprite[_Idx]; }
	int GetMaxFrameCount() { return (int)m_vecSprite.size(); }


// 추가
	bool IsFinish() { return m_bFinish; }



private:
	vector<Ptr<qSprite>>	m_vecSprite;

// 추가
private:
	bool					m_bFinish;
};

