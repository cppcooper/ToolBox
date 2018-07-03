#ifndef _WINFS_TOOLS_H_
#define _WINFS_TOOLS_H_

#include "3rdParty/dirent.h"
#include <assert.h>
#include <string>
#include <map>
#include <algorithm>
#ifdef _DEBUG
#pragma comment (lib,"tools_winfs_Debug.lib")
#else
#pragma comment (lib,"tools_winfs_Release.lib")
#endif

using std::string;
using f_name = std::string;
using f_path = std::string;
using std::wstring;
using file_extension = string;
using file_directory = std::map<f_name, f_path>;

extern std::string execution_path;
extern std::string& get_exec_path( int directories_to_cut );

class DirReader
{
private:
    DIR* Directory;
    string sDirpath;
    std::map<file_extension, file_directory> File_List;

protected:
    bool dirExists( string dirName_in );

public:
    DirReader(){}
    DirReader( string path );

    void Set_Path( string path );
    void Find_Files();
    file_directory& Get_Files( string extension );
};


#endif
