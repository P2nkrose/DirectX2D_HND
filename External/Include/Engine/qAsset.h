#pragma once
#include "qEntity.h"

class qAsset : public qEntity
{
public:

	template<typename T>
	friend class Ptr;

	friend class qAssetMgr;

public:
	qAsset(ASSET_TYPE _Type);
	qAsset(const qAsset& _Other);
	~qAsset();

	// Asset�� ��� Asset�� �θ����� �Ѵ�. ��, �߻�Ŭ�����̹Ƿ� ���������Լ� ����
	virtual qAsset* Clone() { return nullptr; }

public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }
	ASSET_TYPE GetAssetType() { return m_Type; }

private:
	void SetKey(const wstring& _Key) { m_Key = _Key; }
	void SetRelative(const wstring& _path) { m_RelativePath = _path; }

	void AddRef() { ++m_RefCount; }
	void Release()
	{
		--m_RefCount;

		if (m_RefCount <= 0)
			delete this;
	}

	virtual int Load(const wstring& _FilePath) PURE;
	virtual int Save(const wstring& _FilePath) PURE;


private:
	wstring				m_Key;
	wstring				m_RelativePath;
	const ASSET_TYPE	m_Type;

	int					m_RefCount;
};

