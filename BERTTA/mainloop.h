#include "PID_v1.h"

extern "C" {
	
	__declspec(dllexport) int ramp_test(int last_count);
	__declspec(dllexport) double lauda_tex(int port);
	__declspec(dllexport) void t_ramp2(int enable, int pause, int bypass, int err, double Tinit, double Tset, double Tcurrent, double Tlast, double Tbyp, double Tfail, long int ramp_time, long int elapsed, double sp_old, double step, double reset_last, double count_last, double * params);
	__declspec(dllexport) double hei_query(int port, int q);
	__declspec(dllexport) void ramp_timer(int enable, int pause, long int rt, long int start_time, long int pause_time, long int paused, long int paused_old, long int * params);
__declspec(dllexport) long int time_left(long int rt, long int start_time);
__declspec(dllexport) double hold(int enable, double in1, double in2);
__declspec(dllexport) void elapsed_sec(int enable, int reset, long int last_time, long int elapsed_last, long int * params);
__declspec(dllexport) double t_ramp(int enable, long int ramp_time, long int elapsed, double Tset, double Tcurrent, double Tcurr_prev, int direction);
__declspec(dllexport) long int t_epoch(int enable, long int start_time);
__declspec(dllexport) void stirr(int speed, char * newRpm);
__declspec(dllexport) void rpm(int speed, char * newRpm);
__declspec(dllexport) void temp(float temp, char * newTemp);
__declspec(dllexport) void pump(float speed_, char * newPump);
__declspec(dllexport) void ismatec(int port, double speed);
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
__declspec(dllexport) void elapsed( long int last_time, long int * params);
__declspec(dllexport) void sequencer(double Tset, double Tcurrent, int treshold, int seq_previous, int * params);
__declspec(dllexport) void ramp_watch(int enable, int pause, long int elapsed, long int elapsed_previous, long int elapsed_total, long int * params);
__declspec(dllexport) void seq_count(int in1, int in2, int in3, int in4, int * params);
__declspec(dllexport) long int millisec();
__declspec(dllexport) void time_delay(int start, long int delay, long int start_time, long int start_, long int * params);
__declspec(dllexport) void pump_amount(int enable, int reset, double target, double bal, long int bal_previous, long int bal_start, long int step, long int * params);
__declspec(dllexport) void pump_control(int enable, double amount, double target, long int time_limit, long int start_time, long int * params);
__declspec(dllexport) void shut_down(int sh, int port_lauda, int port_ismatec, int port_heidolph);
}