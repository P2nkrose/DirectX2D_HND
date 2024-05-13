#pragma once


template<typename T, int _Size>
void Delete_Array(T(&_arr)[_Size])
{
	for (int i = 0; i < _Size; ++i)
	{
		if (nullptr != _arr[i])
			delete _arr[i];
	}
}


template<typename T>
void Delete_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}


template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		if (nullptr != pair.second)
			delete pair.second;
	}
	_map.clear();
}


// º¯¼ö ÅÛÇÃ¸´
template<typename T1, typename T2>
constexpr bool IsSame = false;
template<typename T1>
constexpr bool IsSame<T1, T1> = true;



#include "assets.h"
template<typename T>
ASSET_TYPE GetAssetType()
{
	if constexpr (IsSame<T, qMesh>)
		return ASSET_TYPE::MESH;
	//if constexpr (IsSame<T, qMeshData>)
	//	return ASSET_TYPE::MESH_DATA;
	//if constexpr (IsSame<T, qMaterial>)
	//	return ASSET_TYPE::MATERIAL;
	//if constexpr (IsSame<T, qPrefab>)
	//	return ASSET_TYPE::PREFAB;
	//if constexpr (IsSame<T, qTexture>)
	//	return ASSET_TYPE::TEXTURE;
	//if constexpr (IsSame<T, qSound>)
	//	return ASSET_TYPE::SOUND;
	if constexpr (IsSame<T, qGraphicShader>)
		return ASSET_TYPE::GRAPHIC_SHADER;
	if constexpr (IsSame<T, qComputeShader>)
		return ASSET_TYPE::COMPUTE_SHADER;

}