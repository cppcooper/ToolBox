#ifndef _INTERACCESS_H
#define _INTERACCESS_H

#include "STL.h"
#include <tools_logger.h>

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
	logger::FilePolicy m_logFile;
	logger::Log m_logger;
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
	GameAsset* LoadAsset( unsigned int type_ID, std::string FileName );
	logger::Log& GetManagementLog();

	template<class T>
	T* LoadAsset( std::string FileName )
	{
		return Asset_Factory<T>::Instance().LoadAsset( FileName );
	}
	template<class T>
	T* GetAsset( std::string AssetName )
	{
		return Asset_Factory<T>::Instance().GetAsset( AssetName );
	}
};

#endif