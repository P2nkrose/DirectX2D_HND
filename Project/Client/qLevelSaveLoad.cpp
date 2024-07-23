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

	// Level �̸� ����
	SaveWString(_Level->GetName(), File);

	// Level �ȿ� �ִ� Layer �� ����
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = _Level->GetLayer(i);

		// Layer �̸� ����
		SaveWString(pLayer->GetName(), File);

		// Layer �ȿ� �ִ� GameObject �� ����
		const vector<qGameObject*>& vecParents = pLayer->GetParentObjects();

		// Layer �� ������ ParentObject ���� ����
		size_t count = vecParents.size();
		fwrite(&count, sizeof(size_t), 1, File);

		// GameObject ����
		for (size_t i = 0; i < vecParents.size(); ++i)
		{
			SaveGameObject(File, vecParents[i]);
		}
	}

	fclose(File);
}

void qLevelSaveLoad::SaveGameObject(FILE* _File, qGameObject* _Object)
{
	// GameObject �� �̸� ����
	SaveWString(_Object->GetName(), _File);

	// Component�� ���� ����
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		qComponent* pComponent = _Object->GetComponent((COMPONENT_TYPE)i);

		if (nullptr == pComponent)
			continue;

		// Component Type �� ����
		COMPONENT_TYPE Type = pComponent->GetComponentType();
		fwrite(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		pComponent->SaveToFile(_File);
	}

	// Script ���� ����
	// Script ���� ����
	const vector<qScript*> vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script �� �̸� ����
		wstring ScriptName = qScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(ScriptName, _File);

		// Script ���� ����
		vecScripts[i]->SaveToFile(_File);
	}

	// Child ���� ����

}

qLevel* qLevelSaveLoad::LoadLevel(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");
	
	// Level ����
	qLevel* pNewLevel = new qLevel;

	// Level �̸� �ҷ�����
	wstring LevelName;
	LoadWString(LevelName, File);
	pNewLevel->SetName(LevelName);

	// Level �ȿ� �ִ� Layer ���� �ҷ�����
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		qLayer* pLayer = pNewLevel->GetLayer(i);
		
		// Layer �̸� �ҷ�����
		wstring LayerName;
		LoadWString(LayerName, File);
		pLayer->SetName(LayerName);

		// Layer �� ������ ParentObject ���� �ҷ�����
		size_t count = 0;
		fread(&count, sizeof(size_t), 1, File);

		// GameObject �ҷ��ͼ� Layer �� ����ֱ�
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

	// GameObject �� �̸� �ε�
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// Component ���� �ε�

	return pObject;
}
