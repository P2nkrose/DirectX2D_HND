#include "pch.h"
#include "MaterialUI.h"

#include "ListUI.h"
#include "TreeUI.h"
#include "qEditorMgr.h"
#include "ParamUI.h"

#include <Engine/qAssetMgr.h>

MaterialUI::MaterialUI()
	: AssetUI(ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}

void MaterialUI::Update()
{
	Title();

	// 재질 이름
	OutputAssetName();

	Ptr<qMaterial> pMtrl = (qMaterial*)GetAsset().Get();

	// 참조하는 쉐이더 이름
	Ptr<qGraphicShader> pShader = pMtrl->GetShader();
	string Name;

	if (nullptr == pShader)
		Name = "None";
	else
		Name = string(pShader->GetKey().begin(), pShader->GetKey().end());

	// 쉐이더 이름
	ImGui::Text("Name");
	ImGui::SameLine(100);
	ImGui::InputText("##ShaderName", (char*)Name.c_str(), Name.length(), ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<qAsset> pAsset = ((qAsset*)pNode->GetData());
			if (ASSET_TYPE::GRAPHIC_SHADER == pAsset->GetAssetType())
			{
				pMtrl->SetShader((qGraphicShader*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##ShaderBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)qEditorMgr::GetInst()->FindEditorUI("List");
		pListUI->SetName("GraphicShader");
		vector<string> vecMeshNames;
		qAssetMgr::GetInst()->GetAssetNames(ASSET_TYPE::GRAPHIC_SHADER, vecMeshNames);
		pListUI->AddList(vecMeshNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MaterialUI::SelectShader);
		pListUI->SetActive(true);
	}

	// 예쁘게 띄우기
	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("Shader Parameter");


	// Shader Parameter
	ShaderParameter();

}

void MaterialUI::ShaderParameter()
{
	Ptr<qMaterial> pMtrl = (qMaterial*)GetAsset().Get();
	Ptr<qGraphicShader> pShader = pMtrl->GetShader();

	if (nullptr == pShader)
		return;

	// Shader 가 요구하는 파라미터 목록을 가져온다.
	const vector<tScalarParam>& vecScalarParam = pShader->GetScalarParam();
	const vector<tTexParam>& vecTexParam = pShader->GetTexParam();
	
	// Scalar Parameter 대응
	for (size_t i = 0; i < vecScalarParam.size(); ++i)
	{
		switch (vecScalarParam[i].ParamType)
		{
		case INT_0:
		case INT_1:
		case INT_2:
		case INT_3:
		{
			int data = *((int*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragInt(&data, 1, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
			}
		}
			break;
		case FLOAT_0:
		case FLOAT_1:
		case FLOAT_2:
		case FLOAT_3:
		{
			float data = *((float*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragFloat(&data, 0.1f, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
			}
		}
			break;
		case VEC2_0:
		case VEC2_1:
		case VEC2_2:
		case VEC2_3:
		{
			Vec2 data = *((Vec2*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragVec2(&data, 0.1f, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
			}
		}
			break;
		case VEC4_0:
		case VEC4_1:
		case VEC4_2:
		case VEC4_3:
		{
			Vec4 data = *((Vec4*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragVec4(&data, 0.1f, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
			}
		}
			break;
		case MAT_0:
		case MAT_1:
		case MAT_2:
		case MAT_3:
		{
			Matrix data = *((Matrix*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
		}
			break;
		}
	}


	// Texture 파라미터 대응

	for (size_t i = 0; i < vecTexParam.size(); ++i)
	{
		Ptr<qTexture> pCurTex = pMtrl->GetTexParam(vecTexParam[i].ParamType);

		if (ParamUI::InputTexture(pCurTex, vecTexParam[i].strDesc, this, (DELEGATE_1)&MaterialUI::ChangeTexture))
		{
			pMtrl->SetTexParam(vecTexParam[i].ParamType, pCurTex);
			m_SelectTexParam = vecTexParam[i].ParamType;
		}
	}

}


void MaterialUI::SelectShader(DWORD_PTR _ListUI)
{
	Ptr<qMaterial> pMtrl = (qMaterial*)GetAsset().Get();

	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pMtrl->SetShader(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qGraphicShader> pShader = qAssetMgr::GetInst()->FindAsset<qGraphicShader>(strAssetName);

	assert(pShader.Get());

	pMtrl->SetShader(pShader);
}


void MaterialUI::ChangeTexture(DWORD_PTR Param)
{
	// 텍스처 파라미터를 입력받을 재질
	Ptr<qMaterial> pMtrl = (qMaterial*)GetAsset().Get();

	// 마지막으로 선택한 항목이 무엇인지 ListUI를 통해서 알아냄
	ListUI* pListUI = (ListUI*)Param;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pMtrl->SetTexParam(m_SelectTexParam, nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<qTexture> pTex = qAssetMgr::GetInst()->FindAsset<qTexture>(strAssetName);

	assert(pMtrl.Get());

	pMtrl->SetTexParam(m_SelectTexParam, pTex);
}