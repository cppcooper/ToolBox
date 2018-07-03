#ifndef _MOUT_H
#define _MOUT_H

#if defined __WIN32__ || defined __WIN32 || defined __CYGWIN32__ || defined _MSC_VER || defined __MINGW32__

#include "windows.h"
// #include <time.h>
// #include <stdio.h>
// #include "stdlib.h"
// #include <fcntl.h>
// #include "io.h"
// #include "direct.h"
// #include "ntverp.h"

extern char* executablePath;

class Console
{
private:
    static unsigned char instances;
    char pipename[64];
    char cmdline[MAX_PATH];

    HANDLE pipe = INVALID_HANDLE_VALUE;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

#else //Add *nix stuff
#endif
    bool valid = false;

public:
    Console();
    Console(const char title[128]);
    Console(const char title[128], unsigned short x, unsigned short y);
    ~Console();
    void Close();
    bool isValid() const {return valid;}
    void printf(const char* format, ...);
    void print(const char* msg);
};

#endif