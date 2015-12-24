#include "../AssetMgr.h"
#include "../InterAccess.h"
using namespace logger;

Asset_Manager::Asset_Manager()
{
	m_Log = &Asset_Faculties::Instance().GetManagementLog();
	m_Log->Line( INFO ) << "Asset Manager Initialized";
}

Asset_Manager::~Asset_Manager()
{
	m_Log->Line( INFO ) << "Asset Manager Deinitialized";
}

//Returns success - ie. returns false if AssetName was recorded previously
bool Asset_Manager::RecordAsset( std::string AssetName, GameAsset* p )
{
	m_Log->Line( INFO ) << "Recording Asset: " << AssetName << ", Address: " << p;
	return Asset_Table.emplace( AssetName, p ).second;
}

GameAsset* Asset_Manager::GetAsset( std::string AssetName )
{
	m_Log->Line( INFO ) << "Looking for Asset Record: " << AssetName;
	auto it = Asset_Table.find( AssetName );
	if ( it != Asset_Table.end() )
		return it->second;
	return nullptr;
}