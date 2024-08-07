#pragma once
#include "AE_Sub.h"

class AE_Preview : public AE_Sub
{
public:
	friend class AE_Detail;
	friend class AE_SpriteView;

	AE_Preview();
	~AE_Preview();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetAnim(Ptr<qFlipBook> _FlipBook);

private:
	Ptr<qFlipBook>			m_CurFlipBook;

};

