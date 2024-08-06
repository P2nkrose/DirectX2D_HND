#include "pch.h"
#include "AE_Preview.h"

AE_Preview::AE_Preview()
{
}

AE_Preview::~AE_Preview()
{
}

void AE_Preview::Init()
{
}

void AE_Preview::Update()
{
}

void AE_Preview::SetAnim(Ptr<qFlipBook> _FlipBook)
{
	if (m_CurFlipBook == _FlipBook)
		return;

	m_CurFlipBook = _FlipBook;
}
