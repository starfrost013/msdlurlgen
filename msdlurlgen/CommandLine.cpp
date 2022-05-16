#include "CommandLine.h"
#include <string>

using namespace std;

CommandLine CommandLine::Parse(int argCount, char* args[])
{
	auto cmdLine = CommandLine();

	if (argCount < 9)
	{
		ReportError("Some required parameters are missing!");
		cmdLine.FailedToParse = true;
		return cmdLine; 
	}

	for (int i = 0; i < argCount; i++)
	{
		string curOption = args[i];

		// convert every character in the string to lowercase to be case-insensitive
		for (int i = 0; i < curOption.size(); i++) curOption[i] = tolower(curOption[i]);

		if (argCount - i > 0)
		{
			// check for each option
			if (curOption == "-start"
				|| curOption == "-s")
			{
				char* tempString = args[i + 1];

				cmdLine.Start = atol(tempString);
			}
			else if (curOption == "-end"
				|| curOption == "-e")
			{
				char* tempString = args[i + 1];

				cmdLine.End = atol(tempString);
			}
			else if (curOption == "-imagesize"
				|| curOption == "-i")
			{
				char* tempString = args[i + 1];

				cmdLine.ImageSize = tempString;
			}
			else if (curOption == "-filename"
				|| curOption == "-f")
			{
				char* tempString = args[i + 1];

				cmdLine.File = tempString;
			}
			else if (curOption == "-quiet"
				|| curOption == "-q")
			{
				cmdLine.Quiet = true; 
			}
			else if (curOption == "-outfile"
				|| curOption == "-o")
			{
				cmdLine.OutFile = args[i + 1];
			}
			else if (curOption == "-dontrun"
				|| curOption == "-d")
			{
				cmdLine.DontRun = true; 
			}
			else if (curOption == "-forceexecutionpolicy"
				|| curOption == "-fe")
			{
				cmdLine.ForceExecutionPolicy = true; 
			}
		}
	}

	// Does some final sanity checks.
	if (cmdLine.Start <= 0
		|| cmdLine.End <= 0) // make sure we have valid unix time values
	{
		ReportError("Invalid -start or -end parameter (must be positive)!");
		cmdLine.FailedToParse = true;
		return cmdLine;
	}

	if (cmdLine.End < cmdLine.Start) // flip end and start if the user accidentally provided them the wrong way around
	{
		long tStart = cmdLine.Start;
		cmdLine.Start = cmdLine.End;
		cmdLine.End = tStart;
	}

	if (strlen(cmdLine.ImageSize) == 0) // make sure the imagesize was provided
	{
		ReportError("Invalid -imagesize parameter!");
		cmdLine.FailedToParse = true;
		return cmdLine;
	}

	if (strlen(cmdLine.File) == 0) // make sure the file was provided.
	{
		ReportError("Invalid -file parameter!");
		cmdLine.FailedToParse = true;
		return cmdLine;
	}

	return cmdLine; 
}

/// <summary>
/// Shows the help message. Called on lack of parameters.
/// </summary>
void CommandLine::ShowHelp()
{
	PrintVersion();

	cout << "msdlurlgen -start [begin] -end [end] -imagesize [image size] -filename [filename] [args...]" << endl << endl;
	cout << "\x1b[32mRequired parameters:\x1b[37m" << endl;
	cout << "-start [-s]: decimal Unix TimeStamp value to start with" << endl;
	cout << "-end [-e]: decimal Unix TimeStamp value to end at" << endl;
	cout << "-imagesize [-i]: hex-format PE SizeOfImage to use" << endl;
	cout << "-filename [-f]: The filename you wish to check for" << endl << endl; 
	cout << "\x1b[32mOptional parameters:\x1b[37m" << endl;
	cout << "-quiet [-q]: Suppress version output" << endl;
	cout << "-outfile [-o]: File to output to (will output to console if not set)" << endl;
	cout << "-dontrun [-d]: Don't try and run the file after generating. " << endl;
	cout << "-forceexecutionpolicy [-fe]: Try to set the execution policy of PowerShell before running." << endl;
	cout << "\x1b[33mWarning:\x1b[37m Your PowerShell ExecutionPolicy must be set to \"Unrestricted\"";
	cout << " in order to run the file after generation. You can run msdlurlgen with -forceexecutionpolicy in order to try and set it to Unrestricted, ";
	cout << "but it, and the download process, will fail if you are not running this tool as administrator. If you need to set your ExecutionPolicy, do it manually or run this app as administrator with the -forceexecutionpolicy option." << endl;
}

