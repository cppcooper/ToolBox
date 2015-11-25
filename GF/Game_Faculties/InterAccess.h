#ifndef _INTERACCESS_H
#define _INTERACCESS_H

#include "STL.h"

class Asset_Storage;
namespace GameAssets{ class Factory; class GameAsset; }
using namespace GameAssets;

class Asset_Faculties
{
	friend class Asset_Pool;
	template<class T>
	friend class Asset_Factory;
	friend class Asset_Loader;
	friend class Asset_Manager;
private:
	Asset_Manager* Manager = nullptr;
	Asset_Loader* Loader = nullptr;
	std::vector<Factory*> Factories;
	Asset_Pool* Pool = nullptr;
	Asset_Storage* Allocator = nullptr;

	Asset_Faculties();
	~Asset_Faculties();

public:
	static Asset_Faculties& Instance();
	
	void Update( double& seconds );
	void RegisterAssetPath( std::string path );
	void LoadAssets();
	GameAsset* GetAsset( std::string AssetName );
	template<class T>
	T* GetAsset( std::string AssetName )
	{
		return Asset_Factory<T>::Instance().GetAsset( AssetName );
	}
};

#endif