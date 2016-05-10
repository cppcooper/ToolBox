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

Object_Faculties::Object_Faculties()
{
	Allocator = new Object_Storage;
	Pool = new Object_Pool;
	Loader = new Asset_Loader;
	Manager = new Asset_Manager;
	GetLog().Line( _INFO ) << "Asset Faculties Initialized";
}

Object_Faculties::~Object_Faculties()
{
	delete Manager;
	delete Loader;
	delete Pool;
	delete Allocator;
	GetLog().Line( _INFO ) << "Asset Faculties Deinitialized";
}

Object_Faculties& Object_Faculties::Instance()
{
	static Object_Faculties instance;
	return instance;
}

void Object_Faculties::Update( double& seconds )
{
}

void Object_Faculties::RegisterAssetPath( std::string path )
{
	GetLog().Line( _INFO ) << "Object_Faculties - Asset Path Registration";
	Loader->RegisterDirectory( path );
}

void Object_Faculties::ReturnPoolObject( GameAssets::ManagedObject* ptr )
{
	Pool->Return( ptr );
}

void Object_Faculties::LoadAssets()
{
	GetLog().Line( _INFO ) << "Object_Faculties - Auto Load Assets";
	Loader->LoadAssets();
}

GameAssets::ManagedObject* Object_Faculties::LoadAsset( unsigned int type_ID, std::string FileName )
{
	GetLog().Line( _INFO ) << "Object_Faculties - Manual Load Asset";
	return Loader->LoadAsset( Factories[type_ID - 1], FileName );
}

logger::Log& Object_Faculties::GetManagementLog()
{
	//TODO: Add log line with call stack trace
	return GetLog();
}