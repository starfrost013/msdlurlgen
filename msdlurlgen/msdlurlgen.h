// Msdlurlgen.h: Global defines for MSDLURLGEN
#pragma once
// msdlurlgen.h: global functions and defines

#include <iostream>
#include <string>
#include "CommandLine.h"

using namespace std;

#define MSDL_VERSION_MAJOR 2;
#define MSDL_VERSION_MINOR 6;
#define MSDL_VERSION_REVISION 1;

void PrintVersion();

void ReportError(string errorString);
