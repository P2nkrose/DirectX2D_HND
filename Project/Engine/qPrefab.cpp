#include "pch.h"
#include "qPrefab.h"

#include "qGameObject.h"

qPrefab::qPrefab()
	: qAsset(ASSET_TYPE::PREFAB)
{
}

qPrefab::~qPrefab()
{
	if (nullptr != m_ProtoObject)
		delete m_ProtoObject;
}

qGameObject* qPrefab::Instantiate()
{
	return m_ProtoObject->Clone();
}

int qPrefab::Load(const wstring& _FilePath)
{
	return 0;
}

int qPrefab::Save(const wstring& _FilePath)
{
	return 0;
}
