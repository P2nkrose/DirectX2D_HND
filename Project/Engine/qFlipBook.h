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

	virtual int Load(const wstring& _FilePath) { return S_OK; }
	virtual int Save(const wstring& _FilePath) { return S_OK; }


public:
	void AddSprite(Ptr<qSprite> _Sprite) { m_vecSprite.push_back(_Sprite); }
	Ptr<qSprite> GetSprite(int _Idx) { return m_vecSprite[_Idx]; }
	int GetMaxFrameCount() { return (int)m_vecSprite.size(); }

private:
	vector<Ptr<qSprite>>	m_vecSprite;
};

