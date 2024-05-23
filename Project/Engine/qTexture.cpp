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
	path filepath = _FilePath;				// 파일의 주소
	path extention = filepath.extension();	// 파일의 확장자

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

	// 알 수 없는 포맷인 경우
	else
	{
		return E_FAIL;
	}

	// 로딩이 실패했을 경우
	if (FAILED(hr))
	{
		errno_t ErrNum = GetLastError();
		WCHAR szBuff[255] = {};
		wsprintf(szBuff, L"Error Number : %d", ErrNum);
		MessageBox(nullptr, szBuff, L"텍스처 로딩 실패", MB_OK);
	}

	// SystemMem(ScratchImage) -> GPU(Texture 2D)

	return S_OK;
}

int qTexture::Save(const wstring& _FilePath)
{
	return 0;
}
