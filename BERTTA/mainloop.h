#include "PID_v1.h"

extern "C" {

__declspec(dllexport) int testfunc(int a);
__declspec(dllexport) void rpm(int speed, char * newRpm);
__declspec(dllexport) void temp(float temp, char * newTemp);

}