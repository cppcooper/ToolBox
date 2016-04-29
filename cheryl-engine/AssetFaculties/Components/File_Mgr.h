#ifndef _FILE_MGR_H_
#define _FILE_MGR_H_

#include "../../../tools_logger.h"
#include "../../../tools_winfs.h"
#include "../STL.h"

class File_Manager
{
private:
	logger::Log* m_Log;
	DirReader Listing_Tool;
	std::unordered_set<std::string> Loaded_Dirs;
	File_Manager();

public:
	~File_Manager();
	static File_Manager& Instance();

	void Register_Directory( std::string path );
	file_directory& Get_Files( std::string extension );
};

#endif
