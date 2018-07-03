#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include <iostream>

CONSOLE_SCREEN_BUFFER_INFO  g_ConsoleBufferInfo;
HANDLE  g_hPipe;
BOOL    g_bExtendedConsole=FALSE;
HANDLE  g_hConsole = INVALID_HANDLE_VALUE;
DWORD   g_dwConsoleSize=0;
COORD   g_dwConsoleCoords;

void CreatePipe(char name[64], char title[128]);
void ReadPipe();

int main(int argc, char* argv[])
{
    if (argc < 3 || argc == 4)
    {
        MessageBox(NULL,"\nMissing Arguments. Argument List={pipeName title bufferX(optional) bufferY(optional)}\n","FAILED",MB_OK);
        return -1;
    }
    if(argc > 5)
    {
        MessageBox(NULL,"Too many arguments (max:4)\nArgument List={pipeName title bufferX(optional) bufferY(optional)}","FAILED",MB_OK);
        return -1;
    }
    char name[64];
    char title[128];
    sprintf(name,"\\\\.\\pipe\\%s",argv[1]);
    sprintf(title,"%s",argv[2]);
    CreatePipe(name, title);

    if(argc == 5)
    {
        COORD coord;
        coord.X=atoi(argv[3]);
        coord.Y=atoi(argv[4]);
        SetConsoleScreenBufferSize( g_hConsole, coord);
    }
    ReadPipe();
    CloseHandle(g_hPipe);
}

void CreatePipe(char name[64], char title[128])
{
    while (1)
    {
        g_hPipe = CreateFile(
            name,   // pipe name
            GENERIC_READ/*|GENERIC_WRITE*/ /* GENERIC_WRITE*/, // read and write access
            0,              // no sharing
            NULL,           // no security attributes
            OPEN_EXISTING,  // opens existing pipe
            0,              // default attributes
            NULL);          // no template file

        // Break if the pipe handle is valid.

        if (g_hPipe != INVALID_HANDLE_VALUE)
            break;

        // Exit if an error other than ERROR_PIPE_BUSY occurs.

        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            MessageBox(NULL,"Could not open pipe(1)","FAILED",MB_OK);
            exit(1);
        }

        // All pipe instances are busy, so wait for 2 seconds.
        printf("Wait for pipe...");
        if (!WaitNamedPipe(name, 20000))
        {
            MessageBox(NULL,"Could not open pipe(2)","FAILED",MB_OK);
            exit(2);
        }
        Sleep(500);
    }
    SetConsoleTitle(title);
    g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(g_hConsole,&g_ConsoleBufferInfo))
    {
        MessageBox(NULL,"GetConsoleScreenBufferInfo failed","FAILURE",MB_OK);
        exit(3);
    }
}

void ReadPipe()
{
    BOOL bSuccess;
    DWORD cbRead,cbWritten;
    char chBuf[1024];
    do
    {
        // Read from the pipe.
        bSuccess = ReadFile(
            g_hPipe,    // pipe handle
            chBuf,    // buffer to receive reply
            sizeof(chBuf),      // size of buffer
            &cbRead,  // number of bytes read
            NULL);    // not overlapped

        if (!bSuccess)
        {
            auto error = GetLastError();
            std::cout << error << std::endl;
            if (error != ERROR_MORE_DATA)
            {
                printf("read failure\n");
                break; // stop only on failure
            }
        }

        // Reply from the pipe is written to STDOUT.  , just like printf...
        if (! WriteFile(g_hConsole,chBuf, cbRead, &cbWritten, NULL))
        {
            printf("write failure\n");
            break;
        }

    } while (true/*!bSuccess*/);  // repeat loop if ERROR_MORE_DATA
}