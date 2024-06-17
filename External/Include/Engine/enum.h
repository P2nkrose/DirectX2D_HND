#pragma once


enum class CB_TYPE
{
	TRANSFORM,		// 렌더링하는 물체의 위치정보, 크기정보
	MATERIAL,		// 재질
	SPRITE,
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
	SPRITE,
	FLIPBOOK,
	END,
};

enum class COMPONENT_TYPE
{
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	FLIPBOOKCOMPONENT,
	ANIMATOR3D,
	STATE_MACHINE,
	RIGIDBODY,
	CAMERA,

	MESHRENDER,
	TILEMAP,
	PARTICLE_SYSTEM,
	DECAl,
	SKYBOX,
	LANDSCAPE,

	END,

	SCRIPT,
};


enum DIR
{
	RIGHT,
	UP,
	FRONT,
};


enum class RS_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,
	END,
};


enum class DS_TYPE
{
	LESS,					// Default값. 깊이가 더 작을때 투영
	LESS_EQUAL,				// 깊이가 작거나 같을 때 투영

	GREATER,				// 깊이가 더 멀어야 투영 (3D에서 쓰임)

	NO_TEST,				// 깊이판정은 하지만, 무조건 다 투영시킴
	NO_TEST_NO_WRITE,		// 깊이판정도 항상 통과시키고, 자신의 깊이 기록도 안함

	END,
};


enum class BS_TYPE
{
	DEFAULT,		// 자기 색상을 그대로 그려줌
	ALPHABLEND,		// 알파값을 적용시키는 알파블랜드
	ONE_ONE,		// 1:1로 합산출력함
	END,
};




enum SCALAR_PARAM
{
	INT_0,		INT_1,		INT_2,		INT_3,
	FLOAT_0,	FLOAT_1,	FLOAT_2,	FLOAT_3,
	VEC2_0,		VEC2_1,		VEC2_2,		VEC2_3,
	VEC4_0,		VEC4_1,		VEC4_2,		VEC4_3,
	MAT_0,		MAT_1,		MAT_2,		MAT_3,
};


enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEXCUBE_0,
	TEXCUBE_1,

	TEXARR_0,
	TEXARR_1,

	END,
};


enum SHADER_DOMAIN
{
	DOMAIN_OPAQUE,		// 불투명
	DOMAIN_MASKED,		// 투명, 불투명
	DOMAIN_TRANSPARENT, // 반투명
	DOMAIN_PARTICLE,	// 파티클

	DOMAIN_DEBUG,		// 디버그
};


enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
	CUBE,
	SPHERE,
};



enum TASK_TYPE
{
	// Param_0 : Layer, Param_1 : Object Adress
	CREATE_OBJECT,

	// Param_0 : Delete Object Adress
	DELETE_OBJECT,
	CHANGE_LEVEL,
	ADD_CHILD,
	COMPONENT_ACTIVATE,
	COMPONENT_DEACTIVATE,
};