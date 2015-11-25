#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include "AssetAbstract.h"
#include "STL.h"
using namespace GameAssets;

class Asset_Manager
{
private:
	std::map<std::string, GameAsset*> Asset_Table;
protected:
public:
	bool RecordAsset( std::string AssetName, GameAsset* p );
	GameAsset* GetAsset( std::string AssetName );
};

#endif