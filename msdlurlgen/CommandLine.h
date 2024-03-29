#pragma once

#include <iostream>
#include "msdlurlgen.h"

using namespace std;

// Defines the commandline options for the application.

class CommandLine
{
public:
	/// <summary>
	/// The image size of the file. In hex format.
	/// </summary>
	char* ImageSize{};

	/// <summary>
	/// The start of the range of the ImageFileDate you are looking for. Decimal unix time format.
	/// </summary>
	long Start{};

	/// <summary>
	/// The end of the range of the ImageFileDate you are looking for. Decimal unix time format.
	/// </summary>
	long End{};

	/// <summary>
	/// The filename you are looking for.
	/// </summary>
	char* File{};

	/// <summary>
	/// Determines if non-essential output will be suppressed.
	/// </summary>
	bool Quiet = false;

	/// <summary>
	/// The filename to output the list of files to.
	/// </summary>
	char* OutFile = nullptr;

	/// <summary>
	/// Determines if the PowerShell script is to be run or not.
	/// </summary>
	bool DontRun = false;

	/// <summary>
	/// Determines if the program will try and force execution policy.
	/// </summary>
	bool ForceExecutionPolicy = false;

	/// <summary>
	/// Parses the command-line arguments.
	/// </summary>
	/// <param name="argCount">The number of arguments passed.</param>
	/// <param name="args">The arguments that have been passed to msdlurlgen</param>
	/// <returns>A pointer to a CommandLine containing the </returns>
	static CommandLine Parse(int argCount, char* args[]);

	/// <summary>
	/// Shows the help message.
	/// </summary>
	static void ShowHelp();

	bool FailedToParse = false;

};