#include "pch.h"
#include "qLevelSaveLoad.h"

#include <Engine/qLevelMgr.h>
#include <Engine/qLevel.h>
#include <Engine/qLayer.h>
#include <Engine/qGameObject.h>
#include <Engine/components.h>

#include <Scripts/qScriptMgr.h>


void qLevelSaveLoad::SaveLevel(const wstring& _FilePath, qLevel* _Level)
{
	assert(_Level);

	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"wb");

	// Level 이름 저장
	SaveWString(_Level->GetName(), File);

	// Level 안에 있는 Layer 를 저장
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = _Level->GetLayer(i);

		// Layer 이름 저장
		SaveWString(pLayer->GetName(), File);

		// Layer 안에 있는 GameObject 를 저장
		const vector<qGameObject*>& vecParents = pLayer->GetParentObjects();

		// Layer 가 보유한 ParentObject 개수 저장
		size_t count = vecParents.size();
		fwrite(&count, sizeof(size_t), 1, File);

		// GameObject 저장
		for (size_t i = 0; i < vecParents.size(); ++i)
		{
			SaveGameObject(File, vecParents[i]);
		}
	}

	fclose(File);
}

void qLevelSaveLoad::SaveGameObject(FILE* _File, qGameObject* _Object)
{
	// GameObject 의 이름 저장
	SaveWString(_Object->GetName(), _File);

	// Component의 정보 저장
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		qComponent* pComponent = _Object->GetComponent((COMPONENT_TYPE)i);

		if (nullptr == pComponent)
			continue;

		// Component Type 을 저장
		COMPONENT_TYPE Type = pComponent->GetComponentType();
		fwrite(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		pComponent->SaveToFile(_File);
	}

	// Script 정보 저장
	// Script 개수 저장
	const vector<qScript*> vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script 의 이름 저장
		wstring ScriptName = qScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(ScriptName, _File);

		// Script 정보 저장
		vecScripts[i]->SaveToFile(_File);
	}

	// Child 정보 저장

}

qLevel* qLevelSaveLoad::LoadLevel(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");
	
	// Level 생성
	qLevel* pNewLevel = new qLevel;

	// Level 이름 불러오기
	wstring LevelName;
	LoadWString(LevelName, File);
	pNewLevel->SetName(LevelName);

	// Level 안에 있는 Layer 정보 불러오기
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = pNewLevel->GetLayer(i);
		
		// Layer 이름 불러오기
		wstring LayerName;
		LoadWString(LayerName, File);
		pLayer->SetName(LayerName);

		// Layer 가 보유한 ParentObject 개수 불러오기
		size_t count = 0;
		fread(&count, sizeof(size_t), 1, File);

		// GameObject 불러와서 Layer 에 집어넣기
		for (size_t i = 0; i < count; ++i)
		{
			qGameObject* pLoadedObject = LoadGameObject(File);
			pLayer->AddObject(pLoadedObject, false);
		}
	}

	fclose(File);
	
	return pNewLevel;
}

qGameObject* qLevelSaveLoad::LoadGameObject(FILE* _File)
{
	qGameObject* pObject = new qGameObject;

	// GameObject 의 이름 로드
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// Component 정보 로드

	return pObject;
}
