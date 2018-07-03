#include <sstream>
#include <string>
#include "../tools_winfs.h"

std::string execution_path = "";

//Returns the file path of the executable being run
std::string& get_exec_path( int directories_to_cut )
{
    ///directories_to_cut specifies how many directory to cut off the result
    static wchar_t buffer[MAX_PATH];
    static bool done = false;
    if ( !done )
    {
        GetModuleFileName( NULL, buffer, MAX_PATH );
        done = true;
    }
    std::wstring unconverted( buffer );
    execution_path = std::string( unconverted.begin(), unconverted.end() );
    execution_path = execution_path.substr( 0, execution_path.find_last_of( "\\" ) );
    for ( int i = 0; i < directories_to_cut; ++i )
    {
        execution_path = execution_path.substr( 0, execution_path.find_last_of( "\\" ) );
    }

    execution_path += "\\";
    return execution_path;
}

bool DirReader::dirExists( string dirName_in )
{
    DWORD ftyp = GetFileAttributesA( dirName_in.c_str() );
    if ( ftyp == INVALID_FILE_ATTRIBUTES )
        return false;  //something is wrong with your path!

    if ( ftyp & FILE_ATTRIBUTE_DIRECTORY )
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

DirReader::DirReader( string path )
{
    Set_Path( path );
}

void DirReader::Set_Path( string path )
{
    Directory = opendir( path.c_str() );
    assert( Directory != NULL );
    this->sDirpath = path;
}

void DirReader::Find_Files()
{
    if ( Directory != NULL )
    {
        dirent *X;
        while ( ( X = readdir( Directory ) ) != NULL )
        {
            string file_name( X->d_name );
            size_t pos = file_name.find_last_of( '.' );
            if ( pos != string::npos )
            {
                string file_ext( file_name.begin() + pos, file_name.end() );
                std::transform( file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower );
                File_List[file_ext][file_name] = sDirpath;
            }
            else
            {
                if ( dirExists( sDirpath + file_name ) )
                    File_List["directories"][file_name] = sDirpath;
                else
                    File_List["file_no_ext"][file_name] = sDirpath;
            }
        }
        closedir( Directory );
    }
}

file_directory& DirReader::Get_Files( string extension )
{
    if ( File_List.size() == 0 )
    {
        Find_Files();
    }
    return File_List[extension];
}
