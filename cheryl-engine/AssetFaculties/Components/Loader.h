#pragma once

#include "../../../tools_logger.h"
#include "../STL.h"
#include "File_Mgr.h"

namespace GameAssets{ class Factory; class GameAsset; }
using namespace GameAssets;

class Asset_Loader
{
	using uint = unsigned int;
private:
	logger::Log* m_Log;
	File_Manager file_mgr = File_Manager::Instance();

protected:
	uint CountAssets( Factory* F );
	void LoadMultiFileAssets( Factory* F );
	void LoadSingleFileAssets( Factory* F );

public:
	Asset_Loader();
	~Asset_Loader();
	void RegisterDirectory( std::string path );
	void LoadAssets();
	GameAsset* LoadAsset( Factory* F, std::string FileName );
	//void UnloadAssets();
};

