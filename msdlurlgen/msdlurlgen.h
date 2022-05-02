// Msdlurlgen.h: Global defines for MSDLURLGEN
#pragma once
// msdlurlgen.h: global functions and defines

#include <iostream>
#include <string>
#include "CommandLine.h"

using namespace std;

#define VERSION_MAJOR 2;
#define VERSION_MINOR 2;
#define VERSION_REVISION 2;

void PrintVersion();

void ReportError(string errorString);
