#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include "AssetAbstract.h"
#include <tools_logger.h>
#include "STL.h"
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
	//TODO: bool RemoveRecord( std::string AssetName );
	GameAsset* GetAsset( std::string AssetName );
};

#endif