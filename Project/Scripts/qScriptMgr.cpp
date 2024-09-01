#include "pch.h"
#include "qScriptMgr.h"

#include "qBookScript_Left.h"
#include "qBookScript_Right.h"
#include "qCameraMoveScript.h"
#include "qComboScript.h"
#include "qCrashScript.h"
#include "qKrushScript.h"
#include "qMissileScript.h"
#include "qPlatformScript.h"
#include "qPlayerScript.h"
#include "qRangeScript.h"

void qScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"qBookScript_Left");
	_vec.push_back(L"qBookScript_Right");
	_vec.push_back(L"qCameraMoveScript");
	_vec.push_back(L"qComboScript");
	_vec.push_back(L"qCrashScript");
	_vec.push_back(L"qKrushScript");
	_vec.push_back(L"qMissileScript");
	_vec.push_back(L"qPlatformScript");
	_vec.push_back(L"qPlayerScript");
	_vec.push_back(L"qRangeScript");
}

qScript * qScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"qBookScript_Left" == _strScriptName)
		return new qBookScript_Left;
	if (L"qBookScript_Right" == _strScriptName)
		return new qBookScript_Right;
	if (L"qCameraMoveScript" == _strScriptName)
		return new qCameraMoveScript;
	if (L"qComboScript" == _strScriptName)
		return new qComboScript;
	if (L"qCrashScript" == _strScriptName)
		return new qCrashScript;
	if (L"qKrushScript" == _strScriptName)
		return new qKrushScript;
	if (L"qMissileScript" == _strScriptName)
		return new qMissileScript;
	if (L"qPlatformScript" == _strScriptName)
		return new qPlatformScript;
	if (L"qPlayerScript" == _strScriptName)
		return new qPlayerScript;
	if (L"qRangeScript" == _strScriptName)
		return new qRangeScript;
	return nullptr;
}

qScript * qScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BOOKSCRIPT_LEFT:
		return new qBookScript_Left;
		break;
	case (UINT)SCRIPT_TYPE::BOOKSCRIPT_RIGHT:
		return new qBookScript_Right;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new qCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::COMBOSCRIPT:
		return new qComboScript;
		break;
	case (UINT)SCRIPT_TYPE::CRASHSCRIPT:
		return new qCrashScript;
		break;
	case (UINT)SCRIPT_TYPE::KRUSHSCRIPT:
		return new qKrushScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new qMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new qPlatformScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new qPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::RANGESCRIPT:
		return new qRangeScript;
		break;
	}
	return nullptr;
}

const wchar_t * qScriptMgr::GetScriptName(qScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BOOKSCRIPT_LEFT:
		return L"qBookScript_Left";
		break;

	case SCRIPT_TYPE::BOOKSCRIPT_RIGHT:
		return L"qBookScript_Right";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"qCameraMoveScript";
		break;

	case SCRIPT_TYPE::COMBOSCRIPT:
		return L"qComboScript";
		break;

	case SCRIPT_TYPE::CRASHSCRIPT:
		return L"qCrashScript";
		break;

	case SCRIPT_TYPE::KRUSHSCRIPT:
		return L"qKrushScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"qMissileScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"qPlatformScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"qPlayerScript";
		break;

	case SCRIPT_TYPE::RANGESCRIPT:
		return L"qRangeScript";
		break;

	}
	return nullptr;
}