#include "pch.h"
#include "Content.h"

#include "TreeUI.h"

#include <Engine/qAssetMgr.h>
#include <Engine/assets.h>

Content::Content()
{
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChild(m_Tree);

	// Ʈ�� �ɼ� ����
	m_Tree->ShowRoot(false);
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Content::AssetClicked);

	// Asset ���¸� Content�� TreeUI�� �ݿ�
	RenewContent();
}

Content::~Content()
{
}

void Content::Update()
{
	// Separator : ���м�
	//ImGui::Separator();

	// Asset Manager ���� ���� Asset ������ ��� �ش�.

}

void Content::RenewContent()
{
	// �θ� ��带 �������� ���� == ��Ʈ��� �Է�
	TreeNode* pRoot = m_Tree->AddNode(nullptr, "Root");

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		TreeNode* pNode = m_Tree->AddNode(pRoot, ToString((ASSET_TYPE)i));
		pNode->SetFrame(true);

		const map<wstring, Ptr<qAsset>>& mapAsset = qAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);

		for (const auto& pair : mapAsset)
		{
			m_Tree->AddNode(pNode, string(pair.first.begin(), pair.first.end()), (DWORD_PTR)pair.second.Get());
		}


	}
}

void Content::AssetClicked(DWORD_PTR _Param)
{
	TreeNode* pNode = (TreeNode*)_Param;
	Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();
}
