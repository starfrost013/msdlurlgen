#include "CommandLine.h"
using namespace std;

CommandLine* CommandLine::Parse(int argc, char* argv[])
{
	auto cmdLine = CommandLine();

	if (argc < 9) return nullptr;

	for (int i = 0; i < argc; i++)
	{
		string curOption = argv[i];

		if (argc - i > 1)
		{
			if (curOption == "-start")
			{
				char* tempString = argv[i + 1];

				cmdLine.Start = atoi(tempString);
			}
			else if (curOption == "-end")
			{
				char* tempString = argv[i + 1];

				cmdLine.End = atoi(tempString);
			}
			else if (curOption == "-imagesize")
			{
				char* tempString = argv[i + 1];

				cmdLine.ImageSize = tempString;
			}
			else if (curOption == "-filename")
			{
				char* tempString = argv[i + 1];

				cmdLine.File = tempString;
			}
		}
	}

	// some final sanity checks

	if (cmdLine.Start <= 0
		|| cmdLine.End <= 0)
	{
		cout << "Invalid start or end parameter (must be positive)!" << endl;
		return nullptr;
	}

	if (strlen(cmdLine.ImageSize) == 0)
	{
		cout << "Invalid ImageSize parameter!" << endl;
		return nullptr; 
	}

	if (strlen(cmdLine.File) == 0)
	{
		cout << "Invalid File parameter!" << endl;
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

	cout << "msdlurlgen -start [begin] -end [end] -imagesize [image size] -filename [filename] " << endl;
	cout << "-start (decimal Unix TimeStamp value to start with)" << endl;
	cout << "-end (decimal Unix TimeStamp value to end at)" << endl;
	cout << "-imagesize (hex-format PE SizeOfImage to use)" << endl;
	cout << "-filename (filename to check for)" << endl;
}

void CommandLine::PrintVersion()
{
	cout << "msdlurlgen Version ";
	cout << VERSION_MAJOR
	cout << "." << VERSION_MINOR;
	cout << "." << VERSION_REVISION;
	cout << " © 2022 starfrost" << endl;
}