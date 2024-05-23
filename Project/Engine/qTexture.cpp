#include "pch.h"
#include "qTexture.h"

qTexture::qTexture()
	: qAsset(ASSET_TYPE::TEXTURE)
	, m_Desc{}
{
}

qTexture::~qTexture()
{
}

void qTexture::Binding()
{
}

int qTexture::Load(const wstring& _FilePath)
{
	path filepath = _FilePath;				// ������ �ּ�
	path extention = filepath.extension();	// ������ Ȯ����

	HRESULT hr = S_OK;

	// *.dds
	if (extention == L".dds" || extention == L".DDS")
	{
		hr = LoadFromDDSFile(_FilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image);
	}

	// *.tga
	else if (extention == L".tga" || extention == L".TGA")
	{
		hr = LoadFromTGAFile(_FilePath.c_str(), nullptr, m_Image);
	}

	// WIC == Window Image Component (*.bmp, *.png, *.jpg, *.jpeg)
	else if (extention == L".bmp" || extention == L".png" || extention == L".jpg" || extention == L".jpeg"
		|| extention == L".BMP" || extention == L".PNG" || extention == L".JPG" || extention == L".JPEG")
	{
		hr = LoadFromWICFile(_FilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image);
	}

	// �� �� ���� ������ ���
	else
	{
		return E_FAIL;
	}

	// �ε��� �������� ���
	if (FAILED(hr))
	{
		errno_t ErrNum = GetLastError();
		WCHAR szBuff[255] = {};
		wsprintf(szBuff, L"Error Number : %d", ErrNum);
		MessageBox(nullptr, szBuff, L"�ؽ�ó �ε� ����", MB_OK);
	}

	// SystemMem(ScratchImage) -> GPU(Texture 2D)

	return S_OK;
}

int qTexture::Save(const wstring& _FilePath)
{
	return 0;
}
