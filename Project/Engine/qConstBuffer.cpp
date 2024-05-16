#include "pch.h"
#include "qConstBuffer.h"

#include "qDevice.h"

qConstBuffer::qConstBuffer()
	: m_Desc{}
{
}

qConstBuffer::~qConstBuffer()
{
}

int qConstBuffer::Create(CB_TYPE _type, UINT _BufferSize)
{
	m_CBType = _type;

	m_Desc.ByteWidth = _BufferSize;
	m_Desc.Usage = D3D11_USAGE_DYNAMIC;
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (FAILED(DEVICE->CreateBuffer(&m_Desc, nullptr, m_CB.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void qConstBuffer::SetData(void* _pData)
{
	// ���������� �ִ� ���� �����͸� ������۷� ����
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);
	memcpy(tMapSub.pData, _pData, m_Desc.ByteWidth);
	CONTEXT->Unmap(m_CB.Get(), 0);
}

void qConstBuffer::Binding()
{
	// ������� ���ε�, b0 �������Ϳ�, Vertex Shader ������, g_CB �� �ִ� ���� 0�� �������Ϳ� ���ε� �� ����
	CONTEXT->VSSetConstantBuffers((UINT)m_CBType, 1, m_CB.GetAddressOf());
}