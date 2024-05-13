#pragma once


enum class CB_TYPE
{
	TRANSFORM,		// �������ϴ� ��ü�� ��ġ����, ũ������
	MATERIAL,		// ����
	GLOBAL,			// ����Ѱ� �����ֱ�
	END,
};


enum class ASSET_TYPE
{
	MESH,
	MESHDATA,
	MATERIAL,
	PREFAB,
	TEXTURE,
	SOUND,
	GRAPHIC_SHADER,
	COMPUTE_SHADER,
	END,
};