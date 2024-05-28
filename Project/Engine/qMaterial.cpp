#include "pch.h"
#include "qMaterial.h"

#include "qDevice.h"
#include "qConstBuffer.h"

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
