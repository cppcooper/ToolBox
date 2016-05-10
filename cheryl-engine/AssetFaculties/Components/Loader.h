#pragma once

#include "../../../tools_logger.h"
#include "../STL.h"
#include "File_Mgr.h"

namespace GameAssets{ class Factory; class AssetObject; }

class Asset_Loader
{
	using uint = unsigned int;
private:
	logger::Log* m_Log;
	File_Manager file_mgr = File_Manager::Instance();

protected:
	uint CountAssets( GameAssets::Factory* F );
	void LoadMultiFileAssets( GameAssets::Factory* F );
	void LoadSingleFileAssets( GameAssets::Factory* F );

public:
	Asset_Loader();
	~Asset_Loader();
	void RegisterDirectory( std::string path );
	void LoadAssets();
	GameAssets::AssetObject* LoadAsset( GameAssets::Factory* F, std::string FileName );
	//void UnloadAssets();
};

