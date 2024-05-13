#pragma once


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
	if (typeid(T).hash_code() == typeid(qMesh).hash_code())
		return ASSET_TYPE::MESH;
	//if (typeid(T).hash_code() == typeid(qMeshData).hash_code())
	//	return ASSET_TYPE::MESH_DATA;
	//if (typeid(T).hash_code() == typeid(qMaterial).hash_code())
	//	return ASSET_TYPE::MATERIAL;
	//if (typeid(T).hash_code() == typeid(qPrefab).hash_code())
	//	return ASSET_TYPE::PREFAB;
	//if (typeid(T).hash_code() == typeid(qTexture).hash_code())
	//	return ASSET_TYPE::TEXTURE;
	//if (typeid(T).hash_code() == typeid(qSound).hash_code())
	//	return ASSET_TYPE::SOUND;
	if (typeid(T).hash_code() == typeid(qGraphicShader).hash_code())
		return ASSET_TYPE::GRAPHIC_SHADER;
	if (typeid(T).hash_code() == typeid(qComputeShader).hash_code())
		return ASSET_TYPE::COMPUTE_SHADER;

}