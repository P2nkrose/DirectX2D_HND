#pragma once
class qLevelSaveLoad
{
public:
	static void SaveLevel(const wstring& _FilePath, qLevel* _Level);
	static void SaveGameObject(FILE* _File, qGameObject* _Object);

	static qLevel* LoadLevel(const wstring& _FilePath);
	static qGameObject* LoadGameObject(FILE* _File);
};

