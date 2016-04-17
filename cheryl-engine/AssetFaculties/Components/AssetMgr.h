#pragma once

#include "../../../tools_logger.h"
#include "../STL.h"
#include "AssetAbstract.h"

using namespace GameAssets;

class Asset_Manager
{
private:
	logger::Log* m_Log;
	std::map<std::string, GameObject*> Asset_Table;
protected:
public:
	Asset_Manager();
	~Asset_Manager();
	bool RecordAsset( std::string AssetName, GameObject* p );
	bool RemoveRecord( std::string AssetName );
	//TODO: bool RemoveRecord( GameObject* p );
	GameObject* GetAsset( std::string AssetName );
};

