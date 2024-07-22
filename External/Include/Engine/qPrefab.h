#pragma once
#include "qAsset.h"

class qPrefab : public qAsset
{
public:
	qPrefab();
	~qPrefab();

public:
	void SetProtoObject(qGameObject* _Object) { m_ProtoObject = _Object; }
	qGameObject* Instantiate();

private:
	virtual int Load(const wstring& _FilePath) override;
	virtual int Save(const wstring& _FilePath) override;


private:
	class qGameObject*		m_ProtoObject;
};

