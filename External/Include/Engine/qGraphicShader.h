#pragma once
#include "qShader.h"

class qGraphicShader : public qShader
{
public:
	qGraphicShader();
	~qGraphicShader();


public:
	int CreateVertexShader(const wstring& _RelativePath, const string& _FuncName);
	int CreatePixelShader(const wstring& _RelativePath, const string& _FuncName);

	void Binding();


public:
	void SetRSType(RS_TYPE _Type) { m_RSType = _Type; }


private:
	// πˆ≈ÿΩ∫ Ω¶¿Ã¥ı (Vertex Shader)
	ComPtr<ID3DBlob>				m_VSBlob;
	ComPtr<ID3D11VertexShader>		m_VS;
									
	// «»ºø Ω¶¿Ã¥ı (Pixel Shader)	
	ComPtr<ID3DBlob>				m_PSBlob;
	ComPtr<ID3D11PixelShader>		m_PS;

	ComPtr<ID3D11InputLayout>		m_Layout;

	D3D11_PRIMITIVE_TOPOLOGY		m_Topolog;

	RS_TYPE							m_RSType;


};

