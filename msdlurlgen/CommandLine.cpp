#include "CommandLine.h"
#include "msdlurlgen.h"
#include <string>

using namespace std;

CommandLine* CommandLine::Parse(int argc, char* argv[])
{
	auto cmdLine = CommandLine();

	if (argc < 9) return nullptr;

	for (int i = 0; i < argc; i++)
	{
		string curOption = argv[i];

		// convert every character in the string to lowercase to be case-insensitive
		for (int i = 0; i < curOption.size(); i++) curOption[i] = tolower(curOption[i]);

		if (argc - i > 0)
		{
			// check for each option
			if (curOption == "-start"
				|| curOption == "-s")
			{
				char* tempString = argv[i + 1];

				cmdLine.Start = atoi(tempString);
			}
			else if (curOption == "-end"
				|| curOption == "-e")
			{
				char* tempString = argv[i + 1];

				cmdLine.End = atoi(tempString);
			}
			else if (curOption == "-imagesize"
				|| curOption == "-i")
			{
				char* tempString = argv[i + 1];

				cmdLine.ImageSize = tempString;
			}
			else if (curOption == "-filename"
				|| curOption == "-f")
			{
				char* tempString = argv[i + 1];

				cmdLine.File = tempString;
			}
			else if (curOption == "-quiet"
				|| curOption == "-q")
			{
				cmdLine.Quiet = true; 
			}
		}
	}

	// Does some final sanity checks.
	if (cmdLine.Start <= 0
		|| cmdLine.End <= 0) // make sure we have valid unix time values
	{
		cout << "Invalid -start or -end parameter (must be positive)!" << endl;
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
		cout << "Invalid -imagesize parameter!" << endl;
		return nullptr; 
	}

	if (strlen(cmdLine.File) == 0) // make sure the file was provided.
	{
		cout << "Invalid -file parameter!" << endl;
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
	cout << "Generates Microsoft Symbol Server request URLs" << endl << endl; // two newlines for S T Y L E 

	cout << "msdlurlgen -start [begin] -end [end] -imagesize [image size] -filename [filename] [args...]" << endl << endl;
	cout << "Required parameters:" << endl;
	cout << "-start [-s] (decimal Unix TimeStamp value to start with)" << endl;
	cout << "-end [-e] (decimal Unix TimeStamp value to end at)" << endl;
	cout << "-imagesize [-i] (hex-format PE SizeOfImage to use)" << endl;
	cout << "-filename [-f] (filename to check for)" << endl << endl; 
	cout << "Optional parameters:" << endl;
	cout << "-quiet [-q]: Suppress version output" << endl;
}

