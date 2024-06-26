#pragma once
#include "qEntity.h"

class qStructuredBuffer : public qEntity
{
public:
	CLONE_DISABLE(qStructuredBuffer);
	qStructuredBuffer();
	~qStructuredBuffer();

public:
	int Create(UINT _ElementSize, UINT _ElementCount, void* _InitData = nullptr);

public:
	UINT GetElementCount() { return m_ElementCount; }
	UINT GetElementSize() { return m_ElementSize; }
	UINT GetBufferSize() { return m_ElementCount * m_ElementSize; }

	void SetData(void* _pData, UINT _DataSize = 0);
	void Binding(UINT _RegisterNum);

private:
	ComPtr<ID3D11Buffer>                m_SB;
	D3D11_BUFFER_DESC                   m_Desc;
	ComPtr<ID3D11ShaderResourceView>    m_SRV;

	UINT                                m_ElementCount;
	UINT                                m_ElementSize;
};

