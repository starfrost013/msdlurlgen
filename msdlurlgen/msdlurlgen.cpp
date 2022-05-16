// msdlurlgen (Legacy C++ version)
// A tool for generating MSDL URLs
// 
// TODO:
// Some refactoring (probably put the generator in a class)
// Not for release, unless you want symsrv to get BTFO'd. 
// Still kind of a bodge due to my "not that much" knowledge of C/C++ but i wanted to challenge myself.

#include <iostream>
#include <fstream>
#include <string>
#include <Shlwapi.h>
#include "CommandLine.h"

using namespace std;

// Global function prototypes.
void GenUrl(CommandLine args);
void GenUrl_WriteToFile(CommandLine args);
void GenUrl_WriteToConsole(CommandLine args);
bool GenUrl_TryRunPs1(CommandLine args);

int main(int argCount, char* args[])
{
    auto parsedArgs = CommandLine::Parse(argCount, args);
    
    // We return a nullptr if an error occurred processing. So we just show the help and exit.
    if (parsedArgs.FailedToParse)
    {
        CommandLine::ShowHelp();
    }
    else
    {
        try
        {
            GenUrl(parsedArgs); // dereference
        }
        catch (exception ex)
        {
            string error_string = "An error occurred while writing the file! Error:\n\n";
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
        cout << endl << "Generating URLs..." << endl;
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

    auto startTime = args.Start;
    auto endTime = args.End;
    char* imageSize = args.ImageSize; // In decimal. It should be padded to at least 0x1000 if you want to have hope
    char* fileName = args.File;
    char* outFile = args.OutFile;

    for (int i = startTime; i <= endTime; i++)
    {
        fileStream << hex << "Invoke-WebRequest \"https://msdl.microsoft.com/download/symbols/" << fileName << "/" << i << imageSize << "/" << fileName << "\"";
        fileStream << "-OutFile " << fileName << endl;
    }

    fileStream.close();

    if (!args.DontRun)
    {
        if (GenUrl_TryRunPs1(args)) cout << "\x1b[32mRunning script at: \x1b[37m" << outFile << "!";
    }
    else
    {
        cout << "\x1b[32mDone! Written to: \x1b[37m" << outFile;
    }
}

/// <summary>
/// Try to run the powershell script we have produced.
/// </summary>
/// <param name="args">The CommandLine instance containing the command-line arguments passed to the application.</param>
bool GenUrl_TryRunPs1(CommandLine args)
{
    char* outFile = args.OutFile;

    // Try to set execution policy. 
    uint32_t execPolicyResult = -1;
    uint32_t cmdResult = -1;

    if (args.ForceExecutionPolicy)
    {
        if (!args.Quiet) cout << endl << "Trying to set execution policy..." << endl;
        execPolicyResult = (uint32_t)ShellExecuteA(NULL, "open", "powershell.exe", "-Command Set-ExecutionPolicy Unrestricted -Force", NULL, SW_HIDE);

        if (execPolicyResult < 32)
        {
            string errString = "Failed to set execution policy! ShellExecuteA returned: ";
            errString.append(to_string(execPolicyResult));

            ReportError(errString);
            return false; 
        }
    }

    if (!args.Quiet) cout << "Running PowerShell script..." << endl;

    // build an std::string containing our parameters
    string psOutFile = "\".\\";
    psOutFile.append(outFile);
    psOutFile.append("\"");

    cmdResult = (uint32_t)ShellExecuteA(NULL, "open", "powershell.exe", psOutFile.c_str(), NULL, SW_SHOW);

    if (cmdResult > 32)
    {
        return true;
    }
    else
    {
        string errString = "Failed to run script! ShellExecuteA returned: ";
        errString.append(to_string(cmdResult));

        ReportError(errString);
        return false; 
    }

    return false; 
}

void GenUrl_WriteToConsole(CommandLine args)
{
    cout << hex;
    auto startTime = args.Start;
    auto endTime = args.End;
    char* imageSize = args.ImageSize; // In decimal. It should be padded to at least 0x1000 if you want to have hope
    char* fileName = args.File;

    for (int i = startTime; i <= endTime; i++)
    {
        cout << hex << "Invoke-WebRequest \"https://msdl.microsoft.com/download/symbols/" << fileName << "/" << i << imageSize << "/" << fileName << "\"";
        cout << " -OutFile " << fileName << endl;
    }
}

void PrintVersion()
{
    // Print out help.
    cout << "\x1b[32m" << "msdlurlgen\x1b[37m Legacy version ";
    cout << MSDL_VERSION_MAJOR;
    cout << "." << MSDL_VERSION_MINOR;
    cout << "." << MSDL_VERSION_REVISION;
    cout << endl << "© 2022 starfrost" << endl;
    cout << "Generates Microsoft Symbol Server request URLs" << endl;
    cout << "\x1b[31mDEPRECATED release! \x1b[32mSymX\x1b[37m version 3.0 with new features coming soon! \x1b[31mSupport will not be provided!\x1b[37m" << endl << endl;
    cout << "\x1b[33mWarning:\x1b[37m " << "I am not responsible for consequences incurred from spam requesting the symbol server. Use responsibly!" << endl;
}

void ReportError(string errorString)
{
    cout << "\x1b[31mError: \x1b[37m" << errorString << endl << endl;
}