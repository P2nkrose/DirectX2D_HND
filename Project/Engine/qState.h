#pragma once
#include "qEntity.h"

#include "qFSM.h"

#include "qFlipBook.h"
#include "qFlipBookComponent.h"
#include "qRigidBody.h"
#include "qCollider2D.h"

class qState : public qEntity
{
public:
	friend class qFSM;

	qState();
	~qState();

public:
	UINT GetStateType() { return m_StateType; }

public:
	virtual void Enter() PURE;
	virtual void FinalTick() PURE;
	virtual void Exit() PURE;


protected:
	qGameObject* GetOwner() { return m_Owner->GetOwner(); }
	qFSM* GetFSM() { return m_Owner; }

	void ChangeState(const wstring& _strStateName);


	template<typename T>
	T GetBlackboardData(const wstring& _DataName)
	{
		return m_Owner->GetBlackboardData<T>(_DataName);
	}

private:
	qFSM*			m_Owner;
	UINT			m_StateType;

};

