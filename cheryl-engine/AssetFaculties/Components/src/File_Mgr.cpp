#include "../File_Mgr.h"
#include "../../InterAccess.h"
using namespace logger;

File_Manager::File_Manager()
{
	m_Log = &Asset_Faculties::Instance().GetManagementLog();
	//m_Log->Line( _INFO ) << "File Manager Initialized.";
}

File_Manager::~File_Manager()
{
	//m_Log->Line( _INFO ) << "File Manager Deinitialized.";
}

File_Manager& File_Manager::Instance()
{
	static File_Manager instance;
	return instance;
}

void File_Manager::Register_Directory( std::string path )
{
	m_Log->Line( _INFO ) << "File_Manager::Register_Directory()";
	///We don't want to load this directory if we've already loaded it
	if ( Loaded_Dirs.emplace( path ).second )
	{
		///We haven't yet loaded this directory
		Listing_Tool.Set_Path( path );
		Listing_Tool.Find_Files();
		///Now we have
		m_Log->Line( _DEBUG1 ) << "Registered and Catalogued"
			<< newl << "Path: " << path;
	}
	else
	{
		m_Log->Line( _ERROR ) << "*Previously* Registered and Catalogued"
			<< newl << "Path: " << path;
	}
}

file_directory& File_Manager::Get_Files( std::string extension )
{
	m_Log->Line( _INFO ) << "File_Manager::Get_Files()";
	m_Log->Line( _DEBUG1 ) << "Getting Catalogued Files"
		<< newl << "Extension Type: " << extension;
	///convert the indicated extension to lower case
	std::transform( extension.begin(), extension.end(), extension.begin(), ::tolower );

	///Look it up, find all matching files
	return Listing_Tool.Get_Files( extension );
}
