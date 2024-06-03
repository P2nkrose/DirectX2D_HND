#include "pch.h"
#include "qLayer.h"

#include "qGameObject.h"

qLayer::qLayer(int _LayerIdx)
	: m_LayerIdx(_LayerIdx)
{
}

qLayer::~qLayer()
{
	Delete_Vec(m_Parents);
}

void qLayer::Begin()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Begin();
	}
}

void qLayer::Tick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->Tick();
	}
}

void qLayer::FinalTick()
{
	for (size_t i = 0; i < m_Parents.size(); ++i)
	{
		m_Parents[i]->FinalTick();
	}
}

void qLayer::AddObject(qGameObject* _Object, bool _bMoveChild)
{
	// 1. ������Ʈ�� �ٸ� ���̾� �Ҽ��� ���
	if (-1 != _Object->GetLayerIdx())
	{
		assert(_Object->GetLayerIdx() != m_LayerIdx);

		// ������ �Ҽӵ� ���̾�� �������;� �Ѵ�.
		_Object->DisconnectWithLayer();
	}

	// 2. �ֻ��� ������Ʈ�� ���
	if (nullptr == _Object->GetParent())
	{
		m_Parents.push_back(_Object);
	}

	// �ڽĵ���� �̵���ų�� ����
	static list<qGameObject*> queue;
	queue.clear();
	queue.push_back(_Object);
	_Object->m_LayerIdx = m_LayerIdx;

	while (!queue.empty())
	{
		qGameObject* pObject = queue.front();
		queue.pop_front();

		if (_bMoveChild || pObject->m_LayerIdx == -1)
		{
			pObject->m_LayerIdx = m_LayerIdx;
		}

		const vector<qGameObject*>& vecChildren = pObject->GetChildren();
		for (size_t i = 0; i < vecChildren.size(); ++i)
		{
			queue.push_back(vecChildren[i]);
		}
	}

}

void qLayer::DisconnectWithObject(qGameObject* _Object)
{
	vector<qGameObject*>::iterator iter = m_Parents.begin();

	for (; iter != m_Parents.end(); ++iter)
	{
		if (_Object == (*iter))
		{
			m_Parents.erase(iter);
			return;
		}
	}

	assert(nullptr);
}


