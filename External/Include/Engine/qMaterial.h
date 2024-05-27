#pragma once
#include "qAsset.h"

class qMaterial : public qAsset
{
public:
	qMaterial();
	~qMaterial();

public:
	virtual int Load(const wstring& _FilePath) override { return S_OK; }
	virtual int Save(const wstring& _FilePath) override { return S_OK; }

public:
	void Binding();
	
	void SetShader(Ptr<qGraphicShader> _Shader) { m_Shader = _Shader; }
	Ptr<qGraphicShader> GetShader() { return m_Shader; }


private:
	Ptr<qGraphicShader>			m_Shader;

};

