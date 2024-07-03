#pragma once
#include "EditorUI.h"

#include <Engine/Ptr.h>
#include <Engine/assets.h>

class qGameObject;
class ComponentUI;
class AssetUI;

class Inspector : public EditorUI
{
public:
	Inspector();
	~Inspector();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SetTargetObject(qGameObject* _Object);
	void SetTargetAsset(Ptr<qAsset> _Asset);

private:
	void CreateComponentUI();
	void CreateAssetUI();


private:
	qGameObject*		m_TargetObject;
	ComponentUI*		m_arrComUI[(UINT)COMPONENT_TYPE::END];

	Ptr<qAsset>			m_TargetAsset;
	AssetUI*			m_arrAssetUI[(UINT)ASSET_TYPE::END];
};

