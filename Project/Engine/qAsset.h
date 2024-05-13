#pragma once
#include "qEntity.h"

class qAsset : public qEntity
{
public:
	friend class qAssetMgr;

public:
	qAsset(ASSET_TYPE _Type);
	~qAsset();

	// Asset�� ��� Asset�� �θ����� �Ѵ�. ��, �߻�Ŭ�����̹Ƿ� ���������Լ� ����
	virtual void Binding() = 0;
	virtual qAsset* Clone() { return nullptr; }

public:
	const wstring& GetKey() { return m_Key; }
	const wstring& GetRelativePath() { return m_RelativePath; }
	ASSET_TYPE GetAssetType() { return m_Type; }

private:
	void SetKey(const wstring& _Key) { m_Key = _Key; }
	void SetRelative(const wstring& _path) { m_RelativePath = _path; }


private:
	wstring				m_Key;
	wstring				m_RelativePath;

	const ASSET_TYPE	m_Type;

};

