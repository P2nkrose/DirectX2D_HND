#pragma once


enum class CB_TYPE
{
	TRANSFORM,		// 렌더링하는 물체의 위치정보, 크기정보
	MATERIAL,		// 재질
	GLOBAL,			// 잡다한거 때려넣기
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