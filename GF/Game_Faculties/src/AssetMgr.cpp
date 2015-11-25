#include "../AssetMgr.h"

bool Asset_Manager::RecordAsset( std::string AssetName, GameAsset* p )
{
	return Asset_Table.emplace( AssetName, p ).second;
}

GameAsset* Asset_Manager::GetAsset( std::string AssetName )
{
	auto it = Asset_Table.find( AssetName );
	if ( it != Asset_Table.end() )
		return it->second;
	return nullptr;
}