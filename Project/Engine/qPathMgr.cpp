#include "pch.h"
#include "qPathMgr.h"

#include "qEngine.h"

qPathMgr::qPathMgr()	
{
}

qPathMgr::~qPathMgr()
{
}

void qPathMgr::Init()
{
	// �����θ� ����
	wchar_t szBuffer[256] = {};
	GetCurrentDirectory(256, szBuffer);

	// bin ������ ���������� �����Ѵ�.
	GetParentPath(szBuffer);

	// \\Content\\ �� �ٿ��д�
	m_Content = szBuffer;
	m_Content += L"\\content\\";	
}

void qPathMgr::render()
{	
}

void qPathMgr::GetParentPath(_Inout_ wchar_t* _Buffer)
{
	size_t len = wcslen(_Buffer);
	
	for (size_t i = len - 1; 0 < i; --i)
	{
		if (L'\\' == _Buffer[i])
		{
			_Buffer[i] = L'\0';
			break;
		}
	}
}
