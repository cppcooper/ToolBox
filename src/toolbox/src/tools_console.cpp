#include "../tools_console.h"
#include <string>
#include <cstring>
#include <cassert>
#include <iostream>

unsigned char Console::instances = 0;
char* executablePath = "C:\\Data\\console.exe";

Console::Console()
    :Console("Console") {}

Console::Console(const char title[128])
    :Console(title, 1024, 1024) {}

Console::Console(const char title[128], unsigned short x, unsigned short y)
{
    assert(pipe == INVALID_HANDLE_VALUE);
    
    char l_title[128] = {0};
    strcpy(l_title, title);
    std::string temp(title);
    size_t pos = temp.find(" ");
    if(pos != std::string::npos)
    {
        char t = '\"';
        temp.insert(temp.begin(),t);
        temp.insert(temp.end(),t);
        strcpy(l_title, temp.c_str());
    }

    char l_pipename[64];
    sprintf(pipename, "%s%d", "pipename", ++instances);
    sprintf(l_pipename, "\\\\.\\pipe\\%s", pipename);
    std::cout << l_pipename << std::endl;
    pipe = CreateNamedPipe(
          l_pipename,               // pipe name
          PIPE_ACCESS_OUTBOUND,     // read/write access, we're only writing...
          PIPE_TYPE_MESSAGE |       // message type pipe
          PIPE_READMODE_BYTE|       // message-read mode
          PIPE_WAIT,                // blocking mode
          1,                        // max. instances
          4096,                     // output buffer size
          0,                        // input buffer size (we don't read data, so 0 is fine)
          1,                        // client time-out
          NULL);                    // no security attribute
    if (pipe==INVALID_HANDLE_VALUE)
    {   // failure
        MessageBox(NULL,"CreateNamedPipe failed","ConsoleLogger failed",MB_OK);
        return;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char cmdline[256] = {0};
    GetStartupInfo(&si);
    sprintf(cmdline,"%s %s %s %d %d", executablePath, pipename, l_title, x, y);
    
    BOOL ret = CreateProcess(NULL,cmdline,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);
    if(!ret)
    {
        MessageBox(NULL,"Couldn't create child process","creation failed",MB_OK);
        return;
    }

    BOOL con = ConnectNamedPipe(pipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
    if(!con)
    {
        MessageBox(NULL,"Couldn't connect to pipe","connection failed",MB_OK);
        return;
    }
    valid = true;
}

Console::~Console()
{
    Close();
    //std::cout << "Console Closed";
}

void Console::Close()
{
    if(valid)
    {
        DisconnectNamedPipe(pipe);
        CloseHandle(pipe);
        valid = false;
    }
}

void Console::printf(const char* format, ...)
{
    DWORD cbWritten;
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf(buffer,format,args);
    WriteFile(pipe,buffer,strlen(buffer),&cbWritten,NULL);
    va_end(args);
}

void Console::print(const char* msg)
{
    DWORD cbWritten;
    WriteFile(pipe,msg,strlen(msg),&cbWritten,NULL);
}