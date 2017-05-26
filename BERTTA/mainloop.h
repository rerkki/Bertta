#include "PID_v1.h"

extern "C" {
	
	__declspec(dllexport) double hei_query(int port, int q);
	__declspec(dllexport) void ramp_timer(int enable, int pause, long int rt, long int start_time, long int pause_time, long int paused, long int paused_old, long int * params);
__declspec(dllexport) long int time_left(long int rt, long int start_time);
__declspec(dllexport) void t_ramp2(long int last_time, double DT, long int * params);
__declspec(dllexport) void elapsed_sec(long int last_time, long int * params);
__declspec(dllexport) double t_ramp(long int ramp_time, long int elapsed, double Tset, double Tcurrent, int direction);
__declspec(dllexport) long int t_epoch(int enable, long int start_time);
__declspec(dllexport) void stirr(int speed, char * newRpm);
__declspec(dllexport) void rpm(int speed, char * newRpm);
__declspec(dllexport) void temp(float temp, char * newTemp);
__declspec(dllexport) void pump(float speed_, char * newPump);
__declspec(dllexport) void ismatec(int port, float speed);
//__declspec(dllexport) void heidolph(int port, int speed, char * output);
__declspec(dllexport) void heidolph(int port, int speed);
__declspec(dllexport) double mettler(int port, int msg);
__declspec(dllexport) void lauda(int port, double set_temp);
__declspec(dllexport) int create_db(void);
__declspec(dllexport) int insert_db(int heidolph, double lauda, double mettler1, double mettler2);
__declspec(dllexport) int getTableData();
__declspec(dllexport) void getColToMat(int col1, int col2, double * values1, double * values2);
__declspec(dllexport) void getColToArr(int col, double * values);
__declspec(dllexport) void TableSave(int exec);
__declspec(dllexport) double pt100(double temp);
__declspec(dllexport) double Compute_PID(double errSum, double lastErr, double Input, double Output_, double Setpoint, double kp, double ki, double kd);
__declspec(dllexport) void elapsed(long int last_time, long int * params);
__declspec(dllexport) long int millisec();

}