#include "pch.h"
#include "qFlipBookComponent.h"

#include "qTimeMgr.h"
#include "qDevice.h"
#include "qConstBuffer.h"

#include "qFlipBook.h"

qFlipBookComponent::qFlipBookComponent()
	: qComponent(COMPONENT_TYPE::FLIPBOOKCOMPONENT)
	, m_CurFlipBook(nullptr)
	, m_CurFrmIdx(0)
{
}

qFlipBookComponent::~qFlipBookComponent()
{
}

void qFlipBookComponent::FinalTick()
{
	if (m_Finish)
	{
		if (false == m_Repeat)
			return;

		Reset();
	}

	if (nullptr != m_CurFlipBook)
	{
		float MaxTime = 1.f / m_FPS;

		m_AccTime += DT;

		if (MaxTime < m_AccTime)
		{
			m_AccTime -= MaxTime;
			++m_CurFrmIdx;

			if (m_CurFlipBook->GetMaxFrameCount() <= m_CurFrmIdx)
			{
				--m_CurFrmIdx;
				m_Finish = true;
			}
		}

		m_CurFrmSprite = m_CurFlipBook->GetSprite(m_CurFrmIdx);
	}
}

void qFlipBookComponent::AddFlipBook(int _Idx, Ptr<qFlipBook> _Flipbook)
{
	if (m_vecFlipBook.size() <= _Idx)
	{
		m_vecFlipBook.resize(_Idx + 1);
	}

	m_vecFlipBook[_Idx] = _Flipbook;
}

Ptr<qFlipBook> qFlipBookComponent::FindFlipBook(const wstring& _Key)
{
	for (size_t i = 0; i < m_vecFlipBook.size(); ++i)
	{
		if (m_vecFlipBook[i]->GetKey() == _Key)
			return m_vecFlipBook[i];
	}

	return nullptr;
}


void qFlipBookComponent::Play(int _FliBookIdx, float _FPS, bool _Repeat)
{
	m_CurFlipBook = m_vecFlipBook[_FliBookIdx];

	if (nullptr == m_CurFlipBook)
	{
		return;
	}

	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_FPS = _FPS;
	m_Repeat = _Repeat;
}


void qFlipBookComponent::Reset()
{
	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_Finish = false;
}

void qFlipBookComponent::Binding()
{
	if (nullptr != m_CurFrmSprite)
	{
		// ���� ǥ���ؾ��ϴ� Sprite �� ������ Sprite ���� ������۸� ���ؼ� GPU �� ����
		tSpriteInfo tInfo = {};

		tInfo.LeftTopUV = m_CurFrmSprite->GetLeftTopUV();
		tInfo.SliceUV = m_CurFrmSprite->GetSliceUV();
		tInfo.BackGroundUV = m_CurFrmSprite->GetBackgroundUV();
		tInfo.OffsetUV = m_CurFrmSprite->GetOffsetUV();
		tInfo.UseFlipbook = 1;

		static qConstBuffer* CB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::SPRITE);

		CB->SetData(&tInfo);
		CB->Binding();

		// FlipBook Sprite ��Ʋ�� �ؽ��� ���� �������͹�ȣ t10 �� ���ε�
		Ptr<qTexture> pAtlas = m_CurFrmSprite->GetAtlasTexture();
		pAtlas->Binding(10);
	}
	else
	{
		Clear();
	}
}

void qFlipBookComponent::Clear()
{
	tSpriteInfo tInfo = {};
	static qConstBuffer* CB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::SPRITE);
	CB->SetData(&tInfo);
	CB->Binding();
}
