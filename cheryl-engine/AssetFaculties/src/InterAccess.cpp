#include "../InterAccess.h"

#include "../Storage.h"
#include "../Pool.h"
#include "../Loader.h"
#include "../AssetMgr.h"


Asset_Faculties::Asset_Faculties() : m_logger( &m_logFile )
{
	assert( m_logFile.Open( "Management.log", false ) );
	m_logger.ReportingLevel() = _DEBUG4;
	Allocator = new Asset_Storage;
	Pool = new Asset_Pool;
	Loader = new Asset_Loader;
	Manager = new Asset_Manager;
	m_logger.Line( _INFO ) << "Asset Faculties Initialized";
}

Asset_Faculties::~Asset_Faculties()
{
	delete Manager;
	delete Loader;
	delete Pool;
	delete Allocator;
	m_logger.Line( _INFO ) << "Asset Faculties Deinitialized";
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
	m_logger.Line( _INFO ) << "Asset_Faculties - Asset Path Registration";
	Loader->RegisterDirectory( path );
}

void Asset_Faculties::LoadAssets()
{
	m_logger.Line( _INFO ) << "Asset_Faculties - Auto Load Assets";
	Loader->LoadAssets();
}

GameAsset* Asset_Faculties::LoadAsset( unsigned int type_ID, std::string FileName )
{
	m_logger.Line( _INFO ) << "Asset_Faculties - Manual Load Asset";
	return Loader->LoadAsset( Factories[type_ID - 1], FileName );
}

logger::Log& Asset_Faculties::GetManagementLog()
{
	//TODO: Add log line with call stack trace
	return m_logger;
}