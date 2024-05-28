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
	void SetDomain(SHADER_DOMAIN _Domain) { m_Domain = _Domain; }
	void SetRSType(RS_TYPE _Type) { m_RSType = _Type; }
	void SetDSType(DS_TYPE _Type) { m_DSType = _Type; }
	void SetBSType(BS_TYPE _Type) { m_BSType = _Type; }

	SHADER_DOMAIN GetDomain() { return m_Domain; }
	RS_TYPE GetRSType() { return m_RSType; }
	DS_TYPE GetDSType() { return m_DSType; }
	BS_TYPE GetBSType() { return m_BSType; }


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
	DS_TYPE							m_DSType;
	BS_TYPE							m_BSType;


	SHADER_DOMAIN					m_Domain;		// Ω¶¿Ã¥ı¿« ∑ª¥ı∏µ πÊΩƒ

};

