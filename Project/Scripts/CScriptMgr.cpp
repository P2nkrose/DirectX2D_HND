#include "pch.h"
#include "CScriptMgr.h"

#include "CScriptMgr.h"
#include "qCameraMoveScript.h"
#include "qMissileScript.h"
#include "qPlayerScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CScriptMgr");
	_vec.push_back(L"qCameraMoveScript");
	_vec.push_back(L"qMissileScript");
	_vec.push_back(L"qPlayerScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CScriptMgr" == _strScriptName)
		return new CScriptMgr;
	if (L"qCameraMoveScript" == _strScriptName)
		return new qCameraMoveScript;
	if (L"qMissileScript" == _strScriptName)
		return new qMissileScript;
	if (L"qPlayerScript" == _strScriptName)
		return new qPlayerScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::SCRIPTMGR:
		return new CScriptMgr;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new qCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new qMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new qPlayerScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::SCRIPTMGR:
		return L"CScriptMgr";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"qCameraMoveScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"qMissileScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"qPlayerScript";
		break;

	}
	return nullptr;
}