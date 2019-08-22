//090619 koodia karsittu ja safe function strcpy_s ja sprintf_s vaihdettu
//UI:t� korjattu




extern "C" {
__declspec(dllexport) double lauda_tin(int port);
//__declspec(dllexport) int ramp_test(int last_count);
__declspec(dllexport) double lauda_tex(int port);
//__declspec(dllexport) void t_ramp2(int res, int enable, int pause, int bypass, int err, double Tinit, double Tset, double Xe, double T_low, double T_up, double Tcurrent, double Tlast, double Tbyp, double Tfail, double Treshold, long int ramp_time, long int elapsed, double sp_old, double step, double reset_last, double count_last, double * params);
__declspec(dllexport) double hei_query(int port, int q);
//__declspec(dllexport) void ramp_timer(int enable, int pause, long int rt, long int start_time, long int pause_time, long int paused, long int paused_old, long int * params);
//__declspec(dllexport) long int time_left(long int rt, long int start_time);
//__declspec(dllexport) double hold(int enable, double in1, double in2);
//__declspec(dllexport) void elapsed_sec(int enable, int reset, long int last_time, long int elapsed_last, long int * params);
//__declspec(dllexport) double t_ramp(int enable, long int ramp_time, long int elapsed, double Tset, double Tcurrent, double Tcurr_prev, int direction);
__declspec(dllexport) void stirr(int speed, char * newRpm);
__declspec(dllexport) void rpm(int speed, char * newRpm);
__declspec(dllexport) void temp(float temp, char * newTemp);
__declspec(dllexport) void pump(float speed_, char * newPump);
__declspec(dllexport) void ismatec(int port, double speed);
__declspec(dllexport) void heidolph(int port, int speed);
__declspec(dllexport) double mettler(int port, int msg);
__declspec(dllexport) void lauda(int port, double set_temp);
//__declspec(dllexport) void Compute_PID(double errSum, double lastErr, double last_time, double last_timeChange, double Input, double Setpoint, double kp, double ki, double kd, double * params);
//__declspec(dllexport) void elapsed( long int last_time, long int * params);
//__declspec(dllexport) void sequencer(double Tset, double Tcurrent, int treshold, int seq_previous, int * params);
//__declspec(dllexport) void ramp_watch(int enable, int pause, long int elapsed, long int elapsed_previous, long int elapsed_total, long int * params);
//__declspec(dllexport) void seq_count(int in1, int in2, int in3, int in4, int * params);
//__declspec(dllexport) long int millisec();
//__declspec(dllexport) void time_delay(int start, long int delay, long int start_time, long int start_, long int * params);
//__declspec(dllexport) void pump_amount(int enable, int reset, double target, double bal, long int bal_previous, long int bal_start, long int step, long int * params);
//__declspec(dllexport) void pump_amount2(int master, int pause, int reset, int count, int manual, double fr_manual, double scale, double elapsed, double * target, double * time_, double * params);
//__declspec(dllexport) void t_ramp3(int master, int pause, int shutdown, int Tr_or_Tj, double Tr, double Tr_last, long int elapsed, double time_err, double * SeqParams, long int * TimeParams, double * params);
//__declspec(dllexport) void t_ramp4(int master, int pause, int reset, int manual, int shutdown, int Tr_or_Tj, double Tr, double adjust, double Tr_last, double start_time, double step_previous, double * SeqParams, long int * TimeParams, double * params);
//__declspec(dllexport) void t_ramp5(int master, int pause, int reset, int manual, int shutdown, int Tr_or_Tj, double Tr, double adjust, double Tr_last, double start_time, double step_previous, double * SeqParams, long int * TimeParams, double * params);
//__declspec(dllexport) void t_ramp6(int master, int pause, int reset, int manual, int shutdown, int Tr_or_Tj, double Tr, double adjust, double Tr_last, double start_time, double step_previous, double * SeqParams, long int * TimeParams, double * params);
//__declspec(dllexport) void pump_control(int enable, double amount, double target, long int time_limit, long int start_time, long int * params);
__declspec(dllexport) void shut_down(int sh, int port_lauda, int port_ismatec, int port_heidolph);
//__declspec(dllexport) void start_time(int enable, long int start_time, long int * params);
//__declspec(dllexport) void flow_pump(double flow, int pump_type, int port, double * pump_ctrl);
//__declspec(dllexport) void hold2(int enable, double in1, double in2, double count, double * params);
//__declspec(dllexport) void fr_ctrl(int enable, int reset, long int last_time, long int elapsed_last, double target, double amount, double amount_last, long int * params);
//__declspec(dllexport) void ramp(int pause, int shutdown, int reset, int grad, int manual, double T_man, long int start_time, long int last_time, long int elapsed_total, long int step, double Tr, double treshold, double * Seq, long int * TimeParams, long int * params);
//__declspec(dllexport) void timer_1(int pause, int reset, long int start_time, long int last_time, long int elapsed_total, long int * params);
__declspec(dllexport) void lauda_switch_mode(int port, int mode, int enable);
//__declspec(dllexport) void pump_amount4(int master, int pause, int reset, int count, int manual, double fr_manual, double scale, double elapsed, double step_previous, double amount_step_previous, double * target, double * time_, double * params);
//__declspec(dllexport) void pump2(int enable, float speed_, char * newPump);
//__declspec(dllexport) void flow_pump2(int enable, int manual, double flow, int pump_type, int port, double * pump_ctrl);
//__declspec(dllexport) double flow_pump3(int enable, int manual, double flow, int port);
__declspec(dllexport) void MReadRS232(int port1, int dev1, int port2, int dev2, int port3, int dev3, int port4, int dev4, int port5, int dev5, int port6, int dev6, int port7, int dev7, int port8, int dev8, double * params);
__declspec(dllexport) void MWriteRS232(int port1, int dev1, double param1, int port2, int dev2, double param2, int port3, int dev3, double param3, int port4, int dev4, double param4);
//__declspec(dllexport) void ramp_simple(int pause, int reset, int master, double elapsed, double time_set, double T0_, double Tr, double Tr_last, double T_sp, double treshold, double * params);
//__declspec(dllexport) void rising_edge(int reset, int input, int prev_input, int prev_count, int * params);
__declspec(dllexport) void lauda_mode(int port, int mode);
__declspec(dllexport) long int millisec3();
//__declspec(dllexport) double mettler1(int port, int msg);
__declspec(dllexport) void FlowIsma(int reset, int enable, int manual, int tube, double density,  double FrManual, double lastTime, double elapsed, double lastErr, double weight, double lastWeight, double lastFr, double errSum, double * Setpoint_W, double * Setpoint_T, double lastSP, double kp, double ki, double kd, int port_isma, int port_mettler, double count, double * PIDparams);
//__declspec(dllexport) void FlowIsma2(int reset, int enable, int manual, int tube, double density, double FrManual, double lastTime, double elapsed, double lastErr, double weight, double lastWeight, double lastFr, double errSum, double * Setpoint_W, double * Setpoint_T, double lastSP, double kp, double ki, double kd, int port_isma, int port_mettler, double count, double * PIDparams);
__declspec(dllexport) void FlowIsma2(double * paramsIn, double * paramsOut);
__declspec(dllexport) void FlowUtil(double * paramsIn, double * paramsOut2);
//__declspec(dllexport) void ramp_v15(int reset, int enable, int manual, double lastTime, double elapsed, double time_set, double T0_, double Tr,  double Tr_last, double T_sp, double treshold, double lastStep, double count, double * params);
__declspec(dllexport) void ramp_v2(int shutdown, int reset, int enable, int count, int manual, int step, int Tr_Tj, int S1_S2, int port_lauda, double lastTime, double elapsed, double T0, double T_S2, double Tr, double T_fail, double Tpause, double treshold, double * time_set, double * time_wait, double * T_sp, double * params);
__declspec(dllexport) void hei_ctrl(int port, int speed, int manual, int shutdown, int prev_status, int * status);
}