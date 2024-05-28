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


#include "assets.h"
template<typename T>
ASSET_TYPE GetAssetType()
{
	if constexpr (std::is_same_v<T, qMesh>)
		return ASSET_TYPE::MESH;
	//if constexpr (std::is_same_v<T, qMeshData>)
	//	return ASSET_TYPE::MESH_DATA;
	if constexpr (std::is_same_v<T, qMaterial>)
		return ASSET_TYPE::MATERIAL;
	//if constexpr (std::is_same_v<T, qPrefab>)
	//	return ASSET_TYPE::PREFAB;
	if constexpr (std::is_same_v<T, qTexture>)
		return ASSET_TYPE::TEXTURE;
	//if constexpr (std::is_same_v<T, qSound>)
	//	return ASSET_TYPE::SOUND;
	if constexpr (std::is_same_v<T, qGraphicShader>)
		return ASSET_TYPE::GRAPHIC_SHADER;
	if constexpr (std::is_same_v<T, qComputeShader>)
		return ASSET_TYPE::COMPUTE_SHADER;

}