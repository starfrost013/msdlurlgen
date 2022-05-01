// msdlurlgen.cpp : This file contains the 'main' function. Program execution begins and ends there.
// TODO:
// COUT manipulators instead of printf_s()
// Saving the file and loading it
// Some refactoring (probably put the generator in a class)
// Not for release, unless you want symsrv to get BTFO'd. 
// Still kind of a bodge due to my "not that much" knowledge of C/C++ but i wanted to challenge myself.

#include <iostream>
#include <string>
#include "CommandLine.h"

using namespace std;

void GenUrl(CommandLine args);

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
        GenUrl(*parsedArgs); // dereference
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

    int startTime = args.Start;
    int endTime = args.End;
    char* imageSize = args.ImageSize; // In decimal. It should be padded to at least 0x1000 if you want to have hope
    char* fileName = args.File;

    /* BAD CODE! printf is terrible and bad */
    /* Todo: use cout modifiers for this */

    for (int i = startTime; i <= endTime; i++)
    {
        printf_s("Invoke-WebRequest \"https://msdl.microsoft.com/download/symbols/%s/%0x%s/%s\" -OutFile \"%s\"\n", fileName, i, imageSize, fileName, fileName);
    }

    /* END BAD CODE */
}

void PrintVersion()
{
    cout << "msdlurlgen version ";
    cout << VERSION_MAJOR;
    cout << "." << VERSION_MINOR;
    cout << "." << VERSION_REVISION;
    cout << endl << "© 2022 starfrost" << endl;
}