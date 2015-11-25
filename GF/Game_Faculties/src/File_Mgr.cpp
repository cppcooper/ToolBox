#include "../File_Mgr.h"

File_Manager::File_Manager()
{}

File_Manager& File_Manager::Instance()
{
	static File_Manager instance;
	return instance;
}

void File_Manager::Register_Directory( std::string path )
{
	///We don't want to load this directory if we've already loaded it
	if ( Loaded_Dirs.emplace( path ).second )
	{
		///We haven't yet loaded this directory
		Listing_Tool.Set_Path( path );
		Listing_Tool.Find_Files();
		///Now we have
	}
}

file_directory& File_Manager::Get_Files( std::string extension )
{
	///convert the indicated extension to lower case
	std::transform( extension.begin(), extension.end(), extension.begin(), ::tolower );

	///Look it up, find all matching files
	return Listing_Tool.Get_Files( extension );
}
