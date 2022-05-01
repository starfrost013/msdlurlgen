#include "CommandLine.h"
#include <string>

using namespace std;

CommandLine* CommandLine::Parse(int argCount, char* args[])
{
	auto cmdLine = CommandLine();

	if (argCount < 9)
	{
		ReportError("Some required parameters are missing!");
		return nullptr;
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

				cmdLine.Start = atoi(tempString);
			}
			else if (curOption == "-end"
				|| curOption == "-e")
			{
				char* tempString = args[i + 1];

				cmdLine.End = atoi(tempString);
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
		}
	}

	// Does some final sanity checks.
	if (cmdLine.Start <= 0
		|| cmdLine.End <= 0) // make sure we have valid unix time values
	{
		ReportError("Invalid -start or -end parameter (must be positive)!");
		return nullptr;
	}

	if (cmdLine.End < cmdLine.Start) // flip end and start if the user accidentally provided them the wrong way around
	{
		int tStart = cmdLine.Start;
		cmdLine.Start = cmdLine.End;
		cmdLine.End = tStart;
	}

	if (strlen(cmdLine.ImageSize) == 0) // make sure the imagesize was provided
	{
		ReportError("Invalid -imagesize parameter!");
		return nullptr; 
	}

	if (strlen(cmdLine.File) == 0) // make sure the file was provided.
	{
		ReportError("Invalid -file parameter!");
		return nullptr;
	}

	return &cmdLine;
}

/// <summary>
/// Shows the help message. Called on lack of parameters.
/// </summary>
void CommandLine::ShowHelp()
{
	PrintVersion();

	cout << "msdlurlgen -start [begin] -end [end] -imagesize [image size] -filename [filename] [args...]" << endl << endl;
	cout << "\x1b[32mRequired parameters:\x1b[37m" << endl;
	cout << "-start [-s] (decimal Unix TimeStamp value to start with)" << endl;
	cout << "-end [-e] (decimal Unix TimeStamp value to end at)" << endl;
	cout << "-imagesize [-i] (hex-format PE SizeOfImage to use)" << endl;
	cout << "-filename [-f] (filename to check for)" << endl << endl; 
	cout << "\x1b[32mOptional parameters:\x1b[37m" << endl;
	cout << "-quiet [-q]: Suppress version output" << endl;
	cout << "-outfile [-o]: File to output to (will output to console if not set)" << endl;
}

