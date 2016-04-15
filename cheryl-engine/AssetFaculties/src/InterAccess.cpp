#include "../InterAccess.h"

#include "../Components/Storage.h"
#include "../Components/Pool.h"
#include "../Components/Loader.h"
#include "../Components/AssetMgr.h"


inline logger::Log& GetLog()
{
	static logger::FilePolicy logFile;
	static logger::Log log( &logFile );
	if ( !logFile.isOpen() )
	{
		assert( logFile.Open( "Management.log", false ) );
		log.ReportingLevel() = _DEBUG4;
	}
	return log;
}

Asset_Faculties::Asset_Faculties()
{
	Allocator = new Asset_Storage;
	Pool = new Asset_Pool;
	Loader = new Asset_Loader;
	Manager = new Asset_Manager;
	GetLog().Line( _INFO ) << "Asset Faculties Initialized";
}

Asset_Faculties::~Asset_Faculties()
{
	delete Manager;
	delete Loader;
	delete Pool;
	delete Allocator;
	GetLog().Line( _INFO ) << "Asset Faculties Deinitialized";
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
	GetLog().Line( _INFO ) << "Asset_Faculties - Asset Path Registration";
	Loader->RegisterDirectory( path );
}

void Asset_Faculties::LoadAssets()
{
	GetLog().Line( _INFO ) << "Asset_Faculties - Auto Load Assets";
	Loader->LoadAssets();
}

GameAsset* Asset_Faculties::LoadAsset( unsigned int type_ID, std::string FileName )
{
	GetLog().Line( _INFO ) << "Asset_Faculties - Manual Load Asset";
	return Loader->LoadAsset( Factories[type_ID - 1], FileName );
}

logger::Log& Asset_Faculties::GetManagementLog()
{
	//TODO: Add log line with call stack trace
	return GetLog();
}