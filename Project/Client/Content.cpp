#include "pch.h"
#include "Content.h"

#include "qEditorMgr.h"
#include "TreeUI.h"
#include "Inspector.h"

#include <Engine/qAssetMgr.h>
#include <Engine/assets.h>

Content::Content()
{
	m_Tree = new TreeUI;
	m_Tree->SetName("ContentTree");
	AddChild(m_Tree);

	// 트리 옵션 세팅
	m_Tree->ShowRoot(false);		// 루트 보이지 않기
	m_Tree->UseDrag(true);			// Tree Drag 기능 ON
	m_Tree->ShowNameOnly(true);		// 노드의 이름에서 경로 및 확장자는 제외하고 파일 이름만 보이기
	m_Tree->AddClickedDelegate(this, (DELEGATE_1)&Content::AssetClicked);

	// Asset 상태를 Content의 TreeUI에 반영
	RenewContent();
}

Content::~Content()
{
}

void Content::Init()
{
	Reload();
}

void Content::Update()
{
	// Separator : 구분선
	//ImGui::Separator();

	// Asset Manager 에서 받은 Asset 정보를 띄워 준다.
	

	// AssetMgr 에 변경점이 생기면, 트리 내용을 재구성한다.
	if (qAssetMgr::GetInst()->IsChanged())
	{
		RenewContent();
	}

}


void Content::RenewContent()
{
	// 트리의 내용을 전부 제거
	m_Tree->Clear();

	// 부모 노드를 지정하지 않음 == 루트노드 입력
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
	if (pNode->IsFrame())
		return;

	Ptr<qAsset> pAsset = (qAsset*)pNode->GetData();

	Inspector* pInspector = (Inspector*)qEditorMgr::GetInst()->FindEditorUI("Inspector");
	pInspector->SetTargetAsset(pAsset);
	ImGui::SetWindowFocus(nullptr);
}


void Content::Reload()
{
	// Content 폴더에 있는 에셋 파일들의 경로를 전부 알아낸다.
	wstring ContentPath = qPathMgr::GetInst()->GetContentPath();
	FindAssetName(ContentPath, L"*.*");

	// 알아낸 에셋 파일들의 경로를 통해서 Asset 들을 AssetMgr 에 로딩한다.
	for (size_t i = 0; i < m_vecAssetPath.size(); ++i)
	{
		m_vecAssetPath[i];
	}
	
	// 에셋 매니저에는 로딩되어 있지만, content 폴더에는 없는 에셋은 AssetMgr에서 삭제하기
}


void Content::FindAssetName(const wstring& _FolderPath, const wstring& _Filter)
{
	WIN32_FIND_DATA tFindData = {};

	// 경로에 맞는 파일 및 폴더를 탐색할 수 있는 커널오브젝트 생성
	wstring strFindPath = _FolderPath + _Filter;
	HANDLE hFinder = FindFirstFile(strFindPath.c_str(), &tFindData);
	assert(hFinder != INVALID_HANDLE_VALUE);

	// 탐색 커널오브젝트를 이용해서 다음 파일을 반복해서 찾아나감
	while (FindNextFile(hFinder, &tFindData))
	{
		wstring strFindName = tFindData.cFileName;

		if (tFindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strFindName == L"..")
				continue;

			FindAssetName(_FolderPath + strFindName + L"\\", _Filter);
		}
		else
		{
			wstring RelativePath = qPathMgr::GetInst()->GetRelativePath(_FolderPath + strFindName);
			m_vecAssetPath.push_back(RelativePath);
		}
	}

	FindClose(hFinder);
}
