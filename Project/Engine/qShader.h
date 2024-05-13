#pragma once
#include "qAsset.h"

class qShader : public qAsset
{
public:
	qShader(ASSET_TYPE _Type);
	~qShader();

protected:
	ComPtr<ID3DBlob>	m_ErrBlob;
};

