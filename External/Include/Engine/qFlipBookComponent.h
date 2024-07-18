#pragma once
#include "qComponent.h"

#include "qFlipBook.h"

class qFlipBookComponent : public qComponent
{
public:
	CLONE(qFlipBookComponent);
	qFlipBookComponent();
	qFlipBookComponent(const qFlipBookComponent& _Origin);
	~qFlipBookComponent();

public:
	virtual void FinalTick() override;


public:
	void AddFlipBook(int _Idx, Ptr<qFlipBook> _FlipBook);
	Ptr<qFlipBook> FindFlipBook(const wstring& _Key);
	void Play(int _FliBookIdx, float _FPS, bool _Repeat);
	Ptr<qSprite> GetCurSprite() { return m_CurFrmSprite; }

	void Reset();
	void Binding();
	static void Clear();


private:
	vector<Ptr<qFlipBook>>			m_vecFlipBook;		// FlipBook ������Ʈ�� ������ ��� FlipBook ���
	Ptr<qFlipBook>					m_CurFlipBook;		// ���� ������� FlipBook
	Ptr<qSprite>					m_CurFrmSprite;		// ���� ������� FlipBook ���� ���� ������ �ε����� �ش��ϴ� ��������Ʈ
	int								m_CurFrmIdx;		// ���� ����߿� FlipBook ���� ���° Sprite�� ��������� �ε��� ���
	int								m_MaxFrm;			// ���� ������� FlipBook �� �ִ� ������
	float							m_FPS;				// ���� ������� FlipBook �� �ʴ� ������ ���� ��
	float							m_AccTime;			// ���� �ð��� üũ
	bool							m_Repeat;
	bool							m_Finish;			// FlipBook ����� ���� �����ߴ��� ����

};

