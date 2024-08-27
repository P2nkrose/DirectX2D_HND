#include "pch.h"
#include "qBlackboard.h"

qBlackboard::qBlackboard()
{
}

qBlackboard::qBlackboard(const qBlackboard& _board)
	: qEntity(_board)
	, m_mapBBData()
{
}

qBlackboard::~qBlackboard()
{
}

void qBlackboard::SetBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	assert(iter == m_mapBBData.end());

	m_mapBBData.insert(make_pair(_strKey, tBlackboardData{ _Type , _Data }));
}

void* qBlackboard::GetBlackboardData(const wstring& _strKey)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	if (iter == m_mapBBData.end())
		return nullptr;

	return iter->second.pData;
}
