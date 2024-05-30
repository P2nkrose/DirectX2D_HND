#pragma once
#include "qComponent.h"

class qGameObejct;

enum PROJ_TYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};


class qCamera : public qComponent
{
public:
	CLONE(qCamera);
	qCamera();
	~qCamera();

public:
	virtual void Begin() override;
	virtual void FinalTick() override;
	void Render();

private:
	void SortGameObject();


public:
	void SetPriority(int _Priority) { m_Priority = _Priority; }
	void SetLayer(UINT _LayerIdx, bool _bCheck)
	{
		if (_bCheck)
			m_LayerCheck |= (1 << _LayerIdx);
		else
			m_LayerCheck &= ~(1 << _LayerIdx);
	}
	void SetLayerAll() { m_LayerCheck = 0xffffffff; }

	
	void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
	PROJ_TYPE GetProjType() { return m_ProjType; }

	void SetFar(float _Far) { m_Far = _Far; }
	float GetFar() { return m_Far; }


private:
	int						m_Priority;				// �켱����
	UINT					m_LayerCheck;			// ���ϴ� ���̾ ī�޶� �������� ����

	PROJ_TYPE				m_ProjType;

	float					m_Width;
	float					m_Height;
	float					m_AspectRatio;			// ��Ⱦ ��
	float					m_Far;					// ī�޶� ���� �ִ� �þ� �Ÿ� (ex : 10000.f)

	float					m_FOV;					// Field Of View (�þ� ����, �þ� ��)

	Matrix					m_matView;
	Matrix					m_matProj;
	

	vector<qGameObject*>	m_vecOpaque;			// ������
	vector<qGameObject*>	m_vecMasked;			// ������, ����
	vector<qGameObject*>	m_vecTransparent;		// ����, ������
	vector<qGameObject*>	m_vecParticles;			// ����, ������, ���� Ÿ��



};

