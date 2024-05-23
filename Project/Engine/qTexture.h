#pragma once
#include "qAsset.h"

class qTexture : public qAsset
{
public:
	CLONE_DISABLE(qTexture);
	qTexture();
	~qTexture();

public:
	virtual void Binding() override;
	virtual int Load(const wstring& _FilePath) override;
	virtual int Save(const wstring& _FilePath) override;

private:
	ScratchImage					m_Image;

	ComPtr<ID3D11Texture2D>			m_Tex2D;
	D3D11_TEXTURE2D_DESC			m_Desc;

};

