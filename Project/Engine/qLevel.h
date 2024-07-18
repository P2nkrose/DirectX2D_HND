#pragma once
#include "qEntity.h"

class qLayer;
class qGameObject;

class qLevel : public qEntity
{
public:
	friend class qTaskMgr;

	virtual qLevel* Clone() { return new qLevel(*this); }
	qLevel();
	qLevel(const qLevel& _Origin);
	~qLevel();

public:
	void Begin();		// ������ ���۵Ǵ� ���� or ������ �߰�(�շ�) �ϴ� ����
	void Tick();
	void FinalTick();

	void ClearObject();

public:
	void AddObject(int LayerIdx, qGameObject* _Object, bool _bMoveChild = false);
	void RegisterAsParent(int LayerIdx, qGameObject* _Object);

	qLayer* GetLayer(int _LayerIdx) { return m_Layer[_LayerIdx]; }
	LEVEL_STATE GetState() { return m_State; }
	qGameObject* FindObjectByName(const wstring& _Name);

private:
	void ChangeState(LEVEL_STATE _NextState);


private:
	qLayer*			m_Layer[MAX_LAYER];
	LEVEL_STATE		m_State;
};

