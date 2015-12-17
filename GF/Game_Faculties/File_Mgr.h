#ifndef _FILE_MGR_H_
#define _FILE_MGR_H_

#include "STL.h"
#include <tools_winfs.h>

class File_Manager
{
private:
	DirReader Listing_Tool;
	std::unordered_set<std::string> Loaded_Dirs;

	File_Manager();

public:
	static File_Manager& Instance();

	void Register_Directory( std::string path );
	file_directory& Get_Files( std::string extension );
};

#endif
