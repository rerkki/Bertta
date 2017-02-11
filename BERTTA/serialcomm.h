#pragma once
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


using namespace std;

__declspec(dllexport) string read(string com_port);


extern "C" {

//	__declspec(dllexport) string read(string com_port);

}