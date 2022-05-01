#pragma once

// Msdlurlgen.h: Global defines for MSDLURLGEN

// Version information (move this to version.h)
#define VERSION_MAJOR 2;
#define VERSION_MINOR 1;
#define VERSION_REVISION 0;

void PrintVersion()
{
	cout << "msdlurlgen version ";
	cout << VERSION_MAJOR;
	cout << "." << VERSION_MINOR;
	cout << "." << VERSION_REVISION;
	cout << endl << "© 2022 starfrost" << endl;
}