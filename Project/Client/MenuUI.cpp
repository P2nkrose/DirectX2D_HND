#include "pch.h"
#include "MenuUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/assets.h>

#include <Scripts/qScriptMgr.h>
#include <Engine/qGameObject.h>
#include <Engine/qScript.h>

#include "qEditorMgr.h"
#include "Inspector.h"


MenuUI::MenuUI()
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::Tick()
{
	if (!IsActive())
		return;

	if (ImGui::BeginMainMenuBar())
	{
		Update();

		ImGui::EndMainMenuBar();
	}
}

void MenuUI::Update()
{
	File();

	Level();

	GameObject();

	Assets();
}

void MenuUI::File()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Level Save"))
		{

		}

		if (ImGui::MenuItem("Level Load"))
		{

		}

		ImGui::EndMenu();
	}
}

void MenuUI::Level()
{
	if (ImGui::BeginMenu("Level"))
	{
		if (ImGui::MenuItem("Play"))
		{

		}

		if (ImGui::MenuItem("Pause"))
		{

		}

		if (ImGui::MenuItem("Stop"))
		{

		}

		ImGui::EndMenu();
	}
}

void MenuUI::GameObject()
{
	if (ImGui::BeginMenu("GameObject"))
	{
		if (ImGui::MenuItem("Create Empty Object"))
		{

		}

		if (ImGui::BeginMenu("Add Component"))
		{
			ImGui::MenuItem("MeshRender");
			ImGui::MenuItem("Collider2D");
			ImGui::MenuItem("camera");

			ImGui::EndMenu();
		}

		AddScript();

		ImGui::EndMenu();
	}
}
  

void MenuUI::AddScript()
{
	if (ImGui::BeginMenu("Add Script"))
	{
		vector<wstring> vecScriptsName;
		qScriptMgr::GetScriptInfo(vecScriptsName);

		for (size_t i = 0; i < vecScriptsName.size(); ++i)
		{
			if (ImGui::MenuItem(string(vecScriptsName[i].begin(), vecScriptsName[i].end()).c_str()))
			{
				qScript* pScript = qScriptMgr::GetScript(vecScriptsName[i]);

				// 인스펙터
				Inspector* pInspector = (Inspector*)qEditorMgr::GetInst()->FindEditorUI("Inspector");

				// 타겟 오브젝트 알아냄
				qGameObject* pObject = pInspector->GetTargetObject();

				if (nullptr != pObject)
				{
					// 오브젝트에, 선택한 스크립트를 추가해줌
					qScript* pScript = qScriptMgr::GetScript(vecScriptsName[i]);
					pObject->AddComponent(pScript);
				}

			}
		}

		ImGui::EndMenu();
	}
}


void MenuUI::Assets()
{
	if (ImGui::BeginMenu("Assets"))
	{
		if (ImGui::MenuItem("Create Empty Material"))
		{
			Ptr<qMaterial> pMtrl = new qMaterial;
			wstring Key = GetAssetKey(ASSET_TYPE::MATERIAL, L"Default Material");
			qAssetMgr::GetInst()->AddAsset<qMaterial>(Key, pMtrl);
			pMtrl->Save(Key);
		}

		if (ImGui::MenuItem("Create Empty FlipBook"))
		{
			EditorUI* pUI = nullptr;

			

			//Ptr<qFlipBook> pFlipBook = new qFlipBook;
			//wstring Key = GetAssetKey(ASSET_TYPE::FLIPBOOK, L"Default FlipBook");
			//qAssetMgr::GetInst()->AddAsset<qFlipBook>(Key, pFlipBook);
		}


		ImGui::EndMenu();
	}
}


wstring MenuUI::GetAssetKey(ASSET_TYPE _Type, const wstring& _Format)
{
	wstring Key;

	switch (_Type)
	{
	case ASSET_TYPE::MATERIAL:
	{
		Key = wstring(L"material\\") + _Format + L" %d.mtrl";
	}
		break;
	case ASSET_TYPE::PREFAB:
	{
		Key = wstring(L"prefab\\") + _Format + L" %d.pref";
	}
		break;
	case ASSET_TYPE::SPRITE:
	{
		Key = wstring(L"sprite\\") + _Format + L" %d.sprite";
	}
		break;
	case ASSET_TYPE::FLIPBOOK:
	{
		Key = wstring(L"flipbook\\") + _Format + L" %d.flip";
	}
		break;
	default:
		assert(nullptr);
		break;
	}

	wchar_t szKey[255] = {};
	wstring FilePath = qPathMgr::GetInst()->GetContentPath();

	for (UINT i = 0; i < 0xffffffff; ++i)
	{
		swprintf_s(szKey, 255, Key.c_str(), i);

		if (false == std::filesystem::exists(FilePath + szKey))
		{
			break;
		}
	}

	return szKey;
}
