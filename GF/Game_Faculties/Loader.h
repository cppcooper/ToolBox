#ifndef _ASSETLOADER_H
#define _ASSETLOADER_H

#include "File_Mgr.h"
#include "STL.h"
namespace GameAssets{ class Factory; }
using namespace GameAssets;

class Asset_Loader
{
	using uint = unsigned int;
private:
	File_Manager file_mgr = File_Manager::Instance();

protected:
	uint CountAssets( Factory* F );
	void LoadMultiFileAssets( Factory* F );
	void LoadSingleFileAssets( Factory* F );

public:
	void RegisterDirectory( std::string path );
	void LoadAssets();
	//void UnloadAssets();
};

#endif