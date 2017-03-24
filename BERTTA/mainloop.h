#include "PID_v1.h"

extern "C" {

__declspec(dllexport) void rpm(int speed, char * newRpm);
__declspec(dllexport) void temp(float temp, char * newTemp);
__declspec(dllexport) void heidolph(int port, int speed, char * output);
__declspec(dllexport) double mettler(int port, int msg);
__declspec(dllexport) void lauda(int port, double set_temp);

}