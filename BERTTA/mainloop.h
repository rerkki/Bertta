#include "PID_v1.h"

extern "C" {

__declspec(dllexport) void rpm(int speed, char * newRpm);
__declspec(dllexport) void temp(float temp, char * newTemp);
//__declspec(dllexport) void heidolph(int port, int speed, char * output);
__declspec(dllexport) void heidolph(int port, int speed);
__declspec(dllexport) double mettler(int port, int msg);
__declspec(dllexport) void lauda(int port, double set_temp);
__declspec(dllexport) int create_db(void);
__declspec(dllexport) int insert_db(int heidolph, double lauda, double mettler1, double mettler2);
__declspec(dllexport) int getTableData();
__declspec(dllexport) void getColToArr(int col, double * values);
__declspec(dllexport) void TableSave(int exec);
__declspec(dllexport) double pt100(double temp);
__declspec(dllexport) double Compute_PID(double errSum, double lastErr, double Input, double Output_, double Setpoint, double kp, double ki, double kd);
__declspec(dllexport) void elapsed(long int last_time, long int * params);
__declspec(dllexport) long int millisec();

}