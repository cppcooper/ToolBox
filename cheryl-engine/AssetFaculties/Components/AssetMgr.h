#pragma once

#include "../../../tools_logger.h"
#include "../STL.h"
#include "AssetAbstract.h"

using namespace GameAssets;

class Asset_Manager
{
private:
	logger::Log* m_Log;
	std::map<std::string, GameAsset*> Asset_Table;
protected:
public:
	Asset_Manager();
	~Asset_Manager();
	bool RecordAsset( std::string AssetName, GameAsset* p );
	bool RemoveRecord( std::string AssetName );
	//TODO: bool RemoveRecord( GameAsset* p );
	GameAsset* GetAsset( std::string AssetName );
};

