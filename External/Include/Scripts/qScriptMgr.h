#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	BOOKSCRIPT_LEFT,
	BOOKSCRIPT_RIGHT,
	CAMERAMOVESCRIPT,
	COLLECTSCRIPT,
	COMBOSCRIPT,
	CRASHSCRIPT,
	DOORSCRIPT,
	DROWNEDSCRIPT,
	ELEVATORSCRIPT,
	KRUSHSCRIPT,
	MISSILESCRIPT,
	PLATFORMSCRIPT,
	PLAYEREFFECTSCRIPT,
	PLAYERHITBOXSCRIPT,
	PLAYERSCRIPT,
	PORTALSCRIPT,
	POSTSCRIPT,
	RANGESCRIPT,
	SKELETONSCRIPT,
	WALLSCRIPT,
};

using namespace std;

class qScript;

class qScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static qScript * GetScript(const wstring& _strScriptName);
	static qScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(qScript * _pScript);
};
