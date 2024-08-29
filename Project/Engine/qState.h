#pragma once
#include "qEntity.h"

#include "qGameObject.h"
#include "qFlipBook.h"
#include "qFlipBookComponent.h"

class qFSM;
class qStateMachine;

class qState : public qEntity
{
public:
	friend class qFSM;
	CLONE_DISABLE(qState);
	qState();
	~qState();

public:
	virtual void Enter() PURE;
	virtual void FinalTick() PURE;
	virtual void Exit() PURE;

	UINT GetStateType() { return m_StateType; }


protected:
	template<typename T>
	T GetBlackboardData(const wstring& _DataName)
	{
		return m_Owner->GetBlackboardData<T>(_DataName);
	}

	qGameObject* GetOwner() { return m_Owner->GetOwner(); }
	qFSM* GetFSM() { return m_Owner; }

	void ChangeState(const wstring& _strStateName);

	virtual void SaveToFile(FILE* _File) {}
	virtual void LoadFromFile(FILE* _File) {}



private:
	qFSM*					m_Owner;

	const UINT              m_StateType;

};
