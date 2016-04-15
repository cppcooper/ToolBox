#include "../AssetMgr.h"
#include "../../InterAccess.h"
using namespace logger;

Asset_Manager::Asset_Manager()
{
	m_Log = &Asset_Faculties::GetManagementLog();
	m_Log->Line( _INFO ) << "Asset Manager Initialized";
}

Asset_Manager::~Asset_Manager()
{
	auto it = Asset_Table.begin();
	for ( ; it != Asset_Table.end(); ++it )
	{
		it->second->Reset();
	}
	m_Log->Line( _INFO ) << "Asset Manager Deinitialized";
}

//Returns success - ie. returns false if AssetName was recorded previously
bool Asset_Manager::RecordAsset( std::string AssetName, GameAsset* p )
{
	m_Log->Line( _INFO ) << "Asset_Manager::RecordAsset()";
	m_Log->Line( _DEBUG1 ) << "Recording Asset"
		<< newl << "Record: " << AssetName
		<< newl << "Address: " << p;
	return Asset_Table.emplace( AssetName, p ).second;
}

bool Asset_Manager::RemoveRecord( std::string AssetName )
{
	auto it = Asset_Table.find( AssetName );
	if ( it != Asset_Table.end() )
	{
		Asset_Table.erase( it );
		return true;
	}
	return false;
}

GameAsset* Asset_Manager::GetAsset( std::string AssetName )
{
	m_Log->Line( _INFO ) << "Asset_Manager::GetAsset()";
	m_Log->Line( _DEBUG1 ) << "Getting Asset"
		<< newl << "Record: " << AssetName;
	auto it = Asset_Table.find( AssetName );
	if ( it != Asset_Table.end() )
		return it->second;

	m_Log->Line( _WARNING ) << "Record Not Found";
	return nullptr;
}