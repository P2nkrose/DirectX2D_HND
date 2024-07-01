#include "pch.h"
#include "qMaterial.h"

#include "qDevice.h"
#include "qConstBuffer.h"

#include "qAssetMgr.h"
#include "qPathMgr.h"

qMaterial::qMaterial()
	: qAsset(ASSET_TYPE::MATERIAL)
{
}

qMaterial::~qMaterial()
{
}

void qMaterial::Binding()
{
	if (!m_Shader)
		return;

	for (int i = 0; i < TEX_PARAM::END; ++i)
	{
		if (nullptr == m_arrTex[i]) {
			m_Const.btex[i] = 0;
			qTexture::Clear(i);
			continue;
		}

		m_Const.btex[i] = 1;
		m_arrTex[i]->Binding(i);
	}

	qConstBuffer* pCB = qDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pCB->SetData(&m_Const);
	pCB->Binding();

	m_Shader->Binding();
}


int qMaterial::Save(const wstring& _RelativePath)
{
	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
	strFilePath += _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"wb");

	if (nullptr == File)
		return E_FAIL;

	// 어떤 쉐이더를 참조 했는지
	SaveAssetRef(m_Shader, File);

	// 상수 데이터
	fwrite(&m_Const, sizeof(tMtrlConst), 1, File);

	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		SaveAssetRef(m_arrTex[i], File);
	}

	fclose(File);

	return S_OK;
}


int qMaterial::Load(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	if (nullptr == File)
		return E_FAIL;

	// 어떤 쉐이더를 참조 했는지
	LoadAssetRef(m_Shader, File);

	// 상수 데이터
	fread(&m_Const, sizeof(tMtrlConst), 1, File);

	for (UINT i = 0; i < TEX_PARAM::END; ++i)
	{
		LoadAssetRef(m_arrTex[i], File);
	}

	fclose(File);

	return S_OK;
}
