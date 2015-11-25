#include "../InterAccess.h"

#include "../Storage.h"
#include "../Pool.h"
#include "../Loader.h"
#include "../AssetMgr.h"


Asset_Faculties::Asset_Faculties()
{
	Allocator = new Asset_Storage;
	Pool = new Asset_Pool;
	Loader = new Asset_Loader;
	Manager = new Asset_Manager;
}

Asset_Faculties::~Asset_Faculties()
{
	delete Manager;
	delete Loader;
	delete Pool;
	delete Allocator;
}

Asset_Faculties& Asset_Faculties::Instance()
{
	static Asset_Faculties instance;
	return instance;
}

void Asset_Faculties::Update( double& seconds )
{
}

void Asset_Faculties::RegisterAssetPath( std::string path )
{
	Loader->RegisterDirectory( path );
}

void Asset_Faculties::LoadAssets()
{
	Loader->LoadAssets();
}

GameAsset* Asset_Faculties::GetAsset( std::string AssetName )
{
	return Manager->GetAsset( AssetName );
}