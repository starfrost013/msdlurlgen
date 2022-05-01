// msdlurlgen
// A tool for generating MSDL URLs
// 
// TODO:
// Saving the file and loading it
// Some refactoring (probably put the generator in a class)
// Not for release, unless you want symsrv to get BTFO'd. 
// Still kind of a bodge due to my "not that much" knowledge of C/C++ but i wanted to challenge myself.

#include <iostream>
#include <fstream>
#include <string>
#include "CommandLine.h"

using namespace std;

// Global function prototypes.
void GenUrl(CommandLine args);
void GenUrl_WriteToFile(CommandLine args);
void GenUrl_WriteToConsole(CommandLine args);

int main(int argCount, char* args[])
{
    auto parsedArgs = CommandLine::Parse(argCount, args);

    // We return a nullptr if an error occurred processing. So we just show the help and exit.
    if (parsedArgs == nullptr)
    {
        CommandLine::ShowHelp();
    }
    else
    {
        try
        {
            GenUrl(*parsedArgs); // dereference
        }
        catch (exception ex)
        {
            string error_string = "An error occurred writing the file! ";
            error_string.append(ex.what());
            ReportError(error_string);
        }
    }
}

void GenUrl(CommandLine args)
{
    // Example for 7950:
    // 2011-02-24 00:00:00 - 1298505600
    // 2011-02-24 23:59:59 - 1298591999. Probably not much compiled after ~10:00
    // based on ntoskrnl (one of the last files, 09:31:56): 1298539916
    
    if (!args.Quiet)
    {
        PrintVersion();
        cout << endl << "URL generation in progress..." << endl << endl;
    }

    if (args.OutFile != nullptr)
    {
        GenUrl_WriteToFile(args);
    }
    else
    {
        GenUrl_WriteToConsole(args);
    }

}

void GenUrl_WriteToFile(CommandLine args)
{
    fstream fileStream;

    fileStream.open(args.OutFile, ios_base::in | ios_base::out | ios_base::trunc);
    fileStream << hex;

    int startTime = args.Start;
    int endTime = args.End;
    char* imageSize = args.ImageSize; // In decimal. It should be padded to at least 0x1000 if you want to have hope
    char* fileName = args.File;

    for (int i = startTime; i <= endTime; i++)
    {
        fileStream << hex << "Invoke-WebRequest \"https://msdl.microsoft.com/download/symbols/" << fileName << "/" << i << imageSize << "/" << fileName << endl;
    }

    fileStream.close();

    cout << "\x1b[32mDone! Written to: \x1b[37m" << args.OutFile;
}

void GenUrl_WriteToConsole(CommandLine args)
{
    cout << hex;
    int startTime = args.Start;
    int endTime = args.End;
    char* imageSize = args.ImageSize; // In decimal. It should be padded to at least 0x1000 if you want to have hope
    char* fileName = args.File;

    for (int i = startTime; i <= endTime; i++)
    {
        cout << hex << "Invoke-WebRequest \"https://msdl.microsoft.com/download/symbols/" << fileName << "/" << i << imageSize << "/" << fileName << endl;
    }
}

void PrintVersion()
{
    cout << "\x1b[32m" << "msdlurlgen\x1b[37m version ";
    cout << VERSION_MAJOR;
    cout << "." << VERSION_MINOR;
    cout << "." << VERSION_REVISION;
    cout << endl << "© 2022 starfrost" << endl;
}

void ReportError(string errorString)
{
    cout << "\x1b[31mError: \x1b[37m" << errorString << endl << endl;
}