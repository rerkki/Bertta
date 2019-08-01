#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include "serialcomm.h"
#include "mainloop.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>

// PID parameters
double Setpoint, Input, Output;

// Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, 1);

__declspec(dllexport) long int millisec3() {

	SYSTEMTIME time;
	GetSystemTime(&time);
	LONG time_ms = (time.wMinute * 60 * 1000) + (time.wSecond * 1000) + time.wMilliseconds;
	return time_ms;

}

__declspec(dllexport) double mettler1(int port, int msg) {

	char * msg_;
	char mettler_str[50] = { 0 };
	char* pEnd;
	string val;
	int msglen;
	int a;
	int v = 0;

	if (msg == 1) msg_ = "SI\r\n";

	strcpy(mettler_str, read(port, 1, msg_).c_str()); 
	Sleep(10); 
	msglen = strlen(mettler_str);

	for (int i = 0; i < msglen; i++) {
		if (isdigit(mettler_str[i])) {
			val += mettler_str[i]; v += 1;
		}
		if (mettler_str[i] == '.') {
			//val += mettler_str[i];  
			v += 1; a = v;
		}
		if (mettler_str[i] == '+') {
			val += mettler_str[i]; v += 1;
		}
		if (mettler_str[i] == '-') {
			val += mettler_str[i]; v += 1;
		}

	}
		//	val[v] = '\0'; 
		int c = pow(10, v - a);
		//	cout << val << "   " << v << "   " << a << "   " << c << endl; 

		return strtod(val.c_str(), &pEnd) / c;

}


__declspec(dllexport) void ramp_v15(int reset, int enable, int manual, double lastTime, double elapsed, double time_set, double T0_, double Tr, double Tr_last, double T_sp, double treshold, double lastStep, double count, double * params) {

	long int now = millisec3();
	long int timeChange = now - lastTime;
	if (timeChange > 6000) timeChange = 6000;
	if (timeChange < 1) timeChange = 1;

	if (enable == 1) {
		elapsed += double(timeChange);
	}

	
	double intercept;

	double slope = 0;

	//	double T0 = Tr;

	double setpoint;

	double step = 0;

	if (reset == 1) {

		params[3] = 0;

		params[4] = Tr_last;

		params[0] = Tr;

		setpoint = Tr_last;

	}

	if (enable == 0 && reset == 0) {

		params[4] = Tr;

		params[0] = T0_;

		if (time_set > 0) {

			slope = (T_sp - T0_) / time_set;

			intercept = T0_;

			setpoint = slope * (elapsed / 60000) + intercept;

		}
		else setpoint = T_sp;

		if (slope > 0 && setpoint > T_sp) {
			setpoint = T_sp;
		}
		if (slope < 0 && setpoint < T_sp) {
			setpoint = T_sp;
		}

	}

	if (enable == 1) {

		if (Tr_last == 0) Tr_last = Tr;

		setpoint = Tr_last;

		if (params[5] == 1) setpoint = T_sp;

		params[4] = Tr_last;

		params[0] = Tr;

	}

	if (enable == 0) setpoint = 20;

	params[6] = 0;
	if (abs(Tr - T_sp) < treshold) {
		step += 1;
	}

	params[1] = setpoint;

	params[2] = slope;

	params[3] = double(now);

	params[6] = step;

	params[7] = elapsed;

}



__declspec(dllexport) void FlowIsma(int reset, int enable, int manual, int tube, double FrManual, double lastTime, double elapsed, double lastErr, double weight, double lastWeight, double lastFr, double errSum, double * Setpoint_W, double * Setpoint_T, double lastSP, double kp, double ki, double kd, int port_isma, int port_mettler, double count, double * PIDparams) {

	long int now = millisec3();
	double RPM = 0;
	long int timeChange = now - lastTime;
	if (timeChange > 6000) timeChange = 6000;
	if (timeChange < 1) timeChange = 1;

	if (enable == 1) {
		elapsed += double(timeChange);
	}

	double weightChange =  lastWeight - weight;

	double Setpoint_W_ = Setpoint_W[0];
	double Setpoint_T_ = Setpoint_T[0];
	double step = 0;
	double step_amount = 0;
	double time_to_target = 0;
	double LED1 = 0;
	double LED2 = 0;
	double LED3 = 0;
	double LED4 = 0;
	double LED5 = 0;
	double LED6 = 0;
	double LED7 = 0;
	double LED_stop = 0;
	double LED_manual = 0;
	double elapsed_step = 0;
	double PumpCTRL = 0;
	double tube_coeff = 0;

	if (tube == 0) tube_coeff = 4.5139; //purple tube
	if (tube == 1) tube_coeff = 1.943; //double purple tube
	if (tube == 2) tube_coeff = 8.0195; //yellow tube
	if (tube == 3) tube_coeff = 16.471; //white tube



	if (step == 0) {
		step_amount = -1 * weight;
		elapsed_step = elapsed / 1000;
	}
	
	if (Setpoint_W[0] > 0) {

		if (-1 * weight > Setpoint_W[0]) {
			Setpoint_W_ = Setpoint_W[1];
			Setpoint_T_ = Setpoint_T[1];
			step_amount = -1 * weight - Setpoint_W[0];
			elapsed_step = (elapsed - Setpoint_T[0] * 60000) / 1000;
			//step = 1;
			step += 1;
		}
		if (-1 * weight > Setpoint_W[0] + Setpoint_W[1]) {
			Setpoint_W_ = Setpoint_W[2];
			Setpoint_T_ = Setpoint_T[2];
			step_amount = -1 * weight - Setpoint_W[0] - Setpoint_W[1];
			elapsed_step = (elapsed - (Setpoint_T[0] + Setpoint_T[1]) * 60000) / 1000;
			//step = 2;
			step += 1;
			time_to_target = 0;
		}
		if (-1 * weight > Setpoint_W[0] + Setpoint_W[1] + Setpoint_W[2]) {
			Setpoint_W_ = Setpoint_W[3];
			Setpoint_T_ = Setpoint_T[3];
			step_amount = -1 * weight - Setpoint_W[0] - Setpoint_W[1] - Setpoint_W[2];
			elapsed_step = (elapsed - (Setpoint_T[0] + Setpoint_T[1] + Setpoint_T[2]) * 60000) / 1000;
			//step = 3;
			step += 1;
			time_to_target = 0;
		}
		if (-1 * weight > Setpoint_W[0] + Setpoint_W[1] + Setpoint_W[2] + Setpoint_W[3]) {
			Setpoint_W_ = Setpoint_W[4];
			Setpoint_T_ = Setpoint_T[4];
			step_amount = -1 * weight - Setpoint_W[0] - Setpoint_W[1] - Setpoint_W[2] - Setpoint_W[3];
			elapsed_step = (elapsed - (Setpoint_T[0] + Setpoint_T[1] + Setpoint_T[2] + Setpoint_T[3]) * 60000) / 1000;
			//step = 4;
			step += 1;
			time_to_target = 0;
		}
		if (-1 * weight > Setpoint_W[0] + Setpoint_W[1] + Setpoint_W[2] + Setpoint_W[3] + Setpoint_W[4]) {
			Setpoint_W_ = Setpoint_W[5];
			Setpoint_T_ = Setpoint_T[5];
			step_amount = -1 * weight - Setpoint_W[0] - Setpoint_W[1] - Setpoint_W[2] - Setpoint_W[3] - Setpoint_W[4];
			elapsed_step = (elapsed - (Setpoint_T[0] + Setpoint_T[1] + Setpoint_T[2] + Setpoint_T[3] + Setpoint_T[4]) * 60000) / 1000;
			elapsed = 0;
			//step = 5;
			step += 1;
			time_to_target = 0;
		}
		if (-1 * weight > Setpoint_W[0] + Setpoint_W[1] + Setpoint_W[2] + Setpoint_W[3] + Setpoint_W[4] + Setpoint_W[5]) {
			Setpoint_W_ = Setpoint_W[6];
			Setpoint_T_ = Setpoint_T[6];
			step_amount = -1 * weight - Setpoint_W[0] - Setpoint_W[1] - Setpoint_W[2] - Setpoint_W[3] - Setpoint_W[4] - Setpoint_W[5];
			elapsed_step = (elapsed - (Setpoint_T[0] + Setpoint_T[1] + Setpoint_T[2] + Setpoint_T[3] + Setpoint_T[4] + Setpoint_T[5]) * 60000) / 1000;
			elapsed = 0;
			//step = 6;
			step += 1;
			time_to_target = 0;
		}
		if (-1 * weight > Setpoint_W[0] + Setpoint_W[1] + Setpoint_W[2] + Setpoint_W[3] + Setpoint_W[4] + Setpoint_W[5] + Setpoint_W[6]) {
			Setpoint_W_ = 0;
			Setpoint_T_ = 1;
			step_amount = -1 * weight - Setpoint_W[0] - Setpoint_W[1] - Setpoint_W[2] - Setpoint_W[3] - Setpoint_W[4] - Setpoint_W[5] - Setpoint_W[6];
			elapsed_step = (elapsed - (Setpoint_T[0] + Setpoint_T[1] + Setpoint_T[2] + Setpoint_T[3] + Setpoint_T[4] + Setpoint_T[5] + Setpoint_T[6]) * 60000) / 1000;
			elapsed = 0;
			//step = 7;
			step += 1;
			time_to_target = 0;
		}
	}
		


	if (elapsed_step < 0) elapsed_step = 0;

	if (manual == 0) {
		if (step == 0) LED1 = 1;
		if (step == 1) LED2 = 1;
		if (step == 2) LED3 = 1;
		if (step == 3) LED4 = 1;
		if (step == 4) LED5 = 1;
		if (step == 5) LED6 = 1;
		if (step == 6) LED7 = 1;
		if (step == 7) LED_stop = 1;
	}

	if (step > 7) step = 7;

//	double fr = 0.3* weightChange*60000 / double(timeChange) + 0.7 * lastFr; // g / min 
	double fr = 0.02* weightChange * 60000 / double(timeChange) + 0.98 * lastFr; // g / min 

	if (fr > 1.1 * Setpoint_W_ / Setpoint_T_) {
		fr = 1.1 * Setpoint_W_ / Setpoint_T_;
		count = 0;
	}
	if (fr < 0.9 * Setpoint_W_ / Setpoint_T_) {
		fr = 0.9 * Setpoint_W_ / Setpoint_T_;
		count = 0;
	}

	double Input = fr * tube_coeff;// 4.5139;

	double Setpoint = (Setpoint_W_ / Setpoint_T_) * tube_coeff;// 4.5139;

//	double error = 0.2*(Setpoint - Input) + 0.8*lastErr;
	double error = 0.2*(Setpoint - Input);
	double errSum_ = errSum + (error * double(timeChange)/60000);
	double dErr = (error - lastErr) / (double(timeChange)/60000);
	double Output_ = kp * error + ki * errSum_ + kd * dErr;

	RPM = Setpoint + Output_;

	if (RPM > 1.2 * Setpoint) {
		RPM = 1.2 * Setpoint;
	}
	if (RPM < 0.8 * Setpoint) {
		RPM = 0.8 * Setpoint;
	}

	if (lastSP != Setpoint) count = 0;

	if (count < 3) {
		RPM = Setpoint;
		fr = Setpoint_W_ / Setpoint_T_;
		count += 1;
	}



	if (fr > 0) {
		time_to_target = 60 * (Setpoint_W_ - step_amount) / fr;
		PumpCTRL = fr * 100 / (Setpoint_W_ / Setpoint_T_);
	}
	else {
		time_to_target = 0;
		PumpCTRL = 0;
	}

	if (LED_stop == 1) PumpCTRL = 100;

//	if (-1 * weight > (Setpoint_W[0] + Setpoint_W[1] + Setpoint_W[2] + Setpoint_W[3] + Setpoint_W[4]) - 1) RPM = 0.3*Setpoint;
	if (time_to_target < 12) RPM = 0.8*Setpoint;
	if (time_to_target < 5) RPM = 0.3*Setpoint;

	if (enable == 0) {
		RPM = 0;
		error = 0;
		errSum_ = 0;
		dErr = 0;
		fr = Setpoint_W_ / Setpoint_T_;
		count = 0;
	}


	if (manual == 1) {
		RPM = FrManual * tube_coeff;// 4.5139;
		LED_manual = 1;
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
		LED4 = 0;
		LED5 = 0;
		LED6 = 0;
		LED7 = 0;
		LED_stop = 0;
	}

	if (reset == 1) {
		step = 0;
		count = 0;
	}


	PIDparams[0] = double(now); //lastTime 
	PIDparams[1] = double(timeChange);
	PIDparams[2] = error;
	PIDparams[3] = errSum_;
	PIDparams[4] = Output_;
	PIDparams[5] = weight;
	PIDparams[6] = Setpoint;
	PIDparams[7] = fr;
	PIDparams[8] = RPM;
	PIDparams[9] = weightChange;
	PIDparams[10] = count;
	PIDparams[11] = step + 1;
	PIDparams[12] = LED1;
	PIDparams[13] = LED2;
	PIDparams[14] = LED3;
	PIDparams[15] = LED4;
	PIDparams[16] = LED5;
	PIDparams[17] = LED_stop;
	PIDparams[18] = LED_manual;
	PIDparams[19] = step_amount;
	PIDparams[20] = time_to_target;
	PIDparams[21] = Setpoint_W_;
	PIDparams[22] = Setpoint_W[0] + Setpoint_W[1] + Setpoint_W[2] + Setpoint_W[3] + Setpoint_W[4] + Setpoint_W[5] + Setpoint_W[6];
	PIDparams[23] = elapsed;
	PIDparams[24] = elapsed_step;
	PIDparams[25] = PumpCTRL;
	PIDparams[26] = LED6;
	PIDparams[27] = LED7;

}



// Function to call Mettler balance, returns weight in grams
__declspec(dllexport) double mettler(int port, int msg) {

	char * msg_;
	char mettler_str[50] = { 0 };
	string val;
	int msglen;

	if (msg == 1) msg_ = "SI\r\n";
	
	strcpy(mettler_str, read(port,1,msg_).c_str());
	Sleep(10);
	msglen = strlen(mettler_str);

	int v = 0;

	for(int i=0;i<msglen;i++) {
		if (isdigit(mettler_str[i])) {
			val += mettler_str[i]; v += 1;
		}
		if (mettler_str[i] == '.') {
			val += mettler_str[i]; v += 1;
		}
		if (mettler_str[i] == '+') {
			val += mettler_str[i]; v += 1;
		}
		if (mettler_str[i] == '-') {
			val += mettler_str[i]; v += 1;
		}

	}
	val[v] = '\0';
	return atof(val.c_str());
	
}

__declspec(dllexport) void hei_ctrl(int port, int speed, int manual, int shutdown, int prev_status, int * status) {

	int status_ = prev_status;
	double a = 0;

	if ((manual == 1) && (status_ == 0)) {
		status_ = 1;
		a = hei_query(port, 5);
	}
	
	if (manual == 0 && shutdown == 0) {
		heidolph(port, speed);
		status_ = 0;
	}

	if (shutdown == 1) {
		heidolph(port, 10);
		status_ = 0;
	}

	status[0] = status_;
}

//muutetaan: palauttaa rpm_arvon (int)
//samanlainen funktio momentille
//__declspec(dllexport) void heidolph(int port, int speed, char * output) {
__declspec(dllexport) void heidolph(int port, int speed) {

	if (port > 0) {
		char rpm_[7] = { 0 };
		stirr(speed, rpm_);
		read(port, 4, rpm_);
		Sleep(60);
	}
	
//	strcpy(output, read(port, 2, rpm_).c_str());
}

__declspec(dllexport) double hei_query(int port, int q) {

	char * msg;
	if (q == 1) msg = "m\r\n";
	if (q == 2) msg = "r\r\n";
	if (q == 3) msg = "A\r\n";
	if (q == 4) msg = "B\r\n";
	if (q == 5) msg = "D\r\n";


	char q_[50] = { 0 };

	string val;

	strcpy(q_, read(port, 5, msg).c_str());

//	cout << q_ << endl;

	Sleep(60);

	int msglen = strlen(q_);

//	cout << msglen << endl;

	int v = 0;

	for (int i = 0; i<msglen; i++) {
		if (isdigit(q_[i])) {
//			cout << q_[i] << endl;
			val += q_[i]; v += 1;
		}
		if (q_[i] == '.') {
//			cout << q_[i];
			val += q_[i]; v += 1;
		}
	}
//	cout << val << endl;
	val[v] = '\0';
	return atof(val.c_str());

}

__declspec(dllexport) double lauda_tex(int port) {

	char * msg;
	msg = "IN_PV_03\r\n";


	char q_[50] = { 0 };

	string val;

	strcpy(q_, read(port, 3, msg).c_str());

//	cout << q_ << endl;

	//Sleep(60);

	int msglen = strlen(q_);
//	cout << msglen << endl;
	int start_msg = 8;
//	if (isdigit(q_[start_msg]) == 0) start_msg = 10;

	//	cout << msglen << endl;

	int v = 0;

	for (int i = start_msg; i<msglen; i++) {
		if (isdigit(q_[i])) {
			//			cout << q_[i] << endl;
			val += q_[i]; v += 1;
		}
		if (q_[i] == '.') {
			//			cout << q_[i];
			val += q_[i]; v += 1;
		}
	}
//	cout << val << endl;
	val[v] = '\0';
	return atof(val.c_str());

}

__declspec(dllexport) double lauda_tin(int port) {

	char * msg;
	msg = "IN_PV_00\r\n";


	char q_[50] = { 0 };

	string val;

	strcpy(q_, read(port, 3, msg).c_str());

	//	cout << q_ << endl;

	//Sleep(60);

	int msglen = strlen(q_);
	//	cout << msglen << endl;
	int start_msg = 8;
	//	if (isdigit(q_[start_msg]) == 0) start_msg = 10;

	//	cout << msglen << endl;

	int v = 0;

	for (int i = start_msg; i<msglen; i++) {
		if (isdigit(q_[i])) {
			//			cout << q_[i] << endl;
			val += q_[i]; v += 1;
		}
		if (q_[i] == '.') {
			//			cout << q_[i];
			val += q_[i]; v += 1;
		}
	}
	//	cout << val << endl;
	val[v] = '\0';
	return atof(val.c_str());

}

__declspec(dllexport) void lauda_mode(int port, int mode) {

	char * msg0;
	msg0 = "OUT_MODE_01_0\r\n";

	char * msg1;
	msg1 = "OUT_MODE_01_1\r\n";

	char q_[50] = { 0 };
	
		if (mode == 0) {

			strcpy(q_, read(port, 2, msg0).c_str());
			cout << q_ << endl;
		}

		if (mode == 1) {

			strcpy(q_, read(port, 2, msg1).c_str());
			cout << q_ << endl;
		}
	
	Sleep(60);

}

__declspec(dllexport) void lauda_switch_mode(int port, int mode, int enable) {

	char * msg0;
	msg0 = "OUT_MODE_01_0\r\n";

	char * msg1;
	msg1 = "OUT_MODE_01_1\r\n";

	char q_[50] = { 0 };

	if (enable == 1) {
		if (mode == 0) {

			strcpy(q_, read(port, 2, msg0).c_str());
			cout << q_ << endl;
		}

		if (mode == 1) {

			strcpy(q_, read(port, 2, msg1).c_str());
			cout << q_ << endl;
		}
	}

	Sleep(60);

}

__declspec(dllexport) void ismatec(int port, double speed) {

	if (port > 0) {
		char rpm_[12] = { 0 };
		pump(speed, rpm_);
		cout << rpm_ << endl;
		read(port, 2, rpm_);
		Sleep(100);
		read(port, 2, "1H\r\n");
		Sleep(60);
	}

}

__declspec(dllexport) void lauda(int port, double set_temp) {

	char temp_[18] = { 0 };
	temp(set_temp, temp_);
	cout << temp_ << endl;
	read(port,3,temp_);
}

__declspec(dllexport) void shut_down(int sh, int port_lauda, int port_ismatec, int port_heidolph) {

	if (sh == 1) {
		lauda(port_lauda, 20);
		Sleep(100);
		ismatec(port_ismatec, 0);
		Sleep(100);
		heidolph(port_heidolph, 0);
	}



}

__declspec(dllexport) void ReadRS232(int port1, int dev1, int port2, int dev2, int port3, int dev3, int port4, int dev4, int port5, int dev5, int port6, int dev6, int port7, int dev7, int port8, int dev8, double * params) {

	if (dev1 == 1) params[0] = mettler1(port1, 1);
	if (dev1 == 2) params[0] = hei_query(port1, 1);
	if (dev1 == 3) params[0] = hei_query(port1, 2);
	if (dev1 == 4) params[0] = lauda_tex(port1);
	if (dev1 == 5) params[0] = lauda_tin(port1);
	if (dev1 == 0) params[0] = 0;

	if (dev2 == 1) params[1] = mettler1(port2, 1);
	if (dev2 == 2) params[1] = hei_query(port2, 1);
	if (dev2 == 3) params[1] = hei_query(port2, 2);
	if (dev2 == 4) params[1] = lauda_tex(port2);
	if (dev2 == 5) params[1] = lauda_tin(port2);
	if (dev2 == 0) params[1] = 0;

	if (dev3 == 1) params[2] = mettler1(port3, 1);
	if (dev3 == 2) params[2] = hei_query(port3, 1);
	if (dev3 == 3) params[2] = hei_query(port3, 2);
	if (dev3 == 4) params[2] = lauda_tex(port3);
	if (dev3 == 5) params[2] = lauda_tin(port3);
	if (dev3 == 0) params[2] = 0;

	if (dev4 == 1) params[3] = mettler1(port4, 1);
	if (dev4 == 2) params[3] = hei_query(port4, 1);
	if (dev4 == 3) params[3] = hei_query(port4, 2);
	if (dev4 == 4) params[3] = lauda_tex(port4);
	if (dev4 == 5) params[3] = lauda_tin(port4);
	if (dev4 == 0) params[3] = 0;

	if (dev5 == 1) params[4] = mettler1(port5, 1);
	if (dev5 == 2) params[4] = hei_query(port5, 1);
	if (dev5 == 3) params[4] = hei_query(port5, 2);
	if (dev5 == 4) params[4] = lauda_tex(port5);
	if (dev5 == 5) params[4] = lauda_tin(port5);
	if (dev5 == 0) params[4] = 0;

	if (dev6 == 1) params[5] = mettler1(port6, 1);
	if (dev6 == 2) params[5] = hei_query(port6, 1);
	if (dev6 == 3) params[5] = hei_query(port6, 2);
	if (dev6 == 4) params[5] = lauda_tex(port6);
	if (dev6 == 5) params[5] = lauda_tin(port6);
	if (dev6 == 0) params[5] = 0;

	if (dev7 == 1) params[6] = mettler1(port7, 1);
	if (dev7 == 2) params[6] = hei_query(port7, 1);
	if (dev7 == 3) params[6] = hei_query(port7, 2);
	if (dev7 == 4) params[6] = lauda_tex(port7);
	if (dev7 == 5) params[6] = lauda_tin(port7);
	if (dev7 == 0) params[6] = 0;

	if (dev8 == 1) params[7] = mettler1(port8, 1);
	if (dev8 == 2) params[7] = hei_query(port8, 1);
	if (dev8 == 3) params[7] = hei_query(port8, 2);
	if (dev8 == 4) params[7] = lauda_tex(port8);
	if (dev8 == 5) params[7] = lauda_tin(port8);
	if (dev8 == 0) params[7] = 0;

}

__declspec(dllexport) double device(int port, int dev) {

	double retval = 0;

	if (dev == 1) retval = lauda_tex(port);
	if (dev == 2) retval = lauda_tin(port);
	if (dev == 3) retval = hei_query(port, 1);
	if (dev == 4) retval = hei_query(port, 2);
	if (dev == 5) retval = mettler(port, 1);
	if (dev < 1 || dev > 5) retval = 0;

	return retval;
}

__declspec(dllexport) void dev_ctrl(int port, int dev, double param) {

	double retval = 0;

	if (dev == 1) lauda(port, param);
	if (dev == 2) ismatec(port, param);
	if (dev == 3) ismatec(port, param); //PID_FLOW

	if (dev < 1 || dev > 3) retval = 0;

}

__declspec(dllexport) void MWriteRS232(int port1, int dev1, double param1, int port2, int dev2, double param2, int port3, int dev3, double param3, int port4, int dev4, double param4) {
	
	thread t1([port1, dev1, param1] {
		dev_ctrl(port1, dev1, param1);
	});

	thread t2([port2, dev2, param2] {
		dev_ctrl(port2, dev2, param2);
	});

	thread t3([port3, dev3, param3] {
		dev_ctrl(port3, dev3, param3);
	});

	thread t4([port4, dev4, param4] {
		dev_ctrl(port4, dev4, param4);
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();

}

__declspec(dllexport) void MReadRS232(int port1, int dev1, int port2, int dev2, int port3, int dev3, int port4, int dev4, int port5, int dev5, int port6, int dev6, int port7, int dev7, int port8, int dev8, double * params) {

	double x1{ 0 };
	double x2{ 0 };
	double x3{ 0 };
	double x4{ 0 };
	double x5{ 0 };
	double x6{ 0 };
	double x7{ 0 };
	double x8{ 0 };


	thread t1( [&x1, &x2, port1, port2, dev1, dev2]{
		x1 = device(port1, dev1);
		x2 = device(port2, dev2);
	});

	thread t2([&x3, &x4, port3, port4, dev3, dev4] {
		x3 = device(port3, dev3);
		x4 = device(port4, dev4);
	});

	thread t3([&x5, port5, dev5] {
		x5 = device(port5, dev5);
	});

	thread t4([&x6, port6, dev6] {
		x6 = device(port6, dev6);
	});

	thread t5([&x7, port7, dev7] {
		x7 = device(port7, dev7);
	});

	thread t6([&x8, port8, dev8] {
		x8 = device(port8, dev8);
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	params[0] = x1;
	params[1] = x2;
	params[2] = x3;
	params[3] = x4;
	params[4] = x5;
	params[5] = x6;
	params[6] = x7;


}



/*
int main() {

	
	double res_vec[8] = { 0 };

	for (int(i) = 0; i < 100; i++) {
	//	ReadRS232(9, 4, 9, 5, 10, 1, 11, 1, 12, 1, 13, 2, 13, 3, 0, 0, res_vec);
	   MReadRS232(1, 1, 1, 2, 2, 3, 2, 4, 3, 5, 4, 5, 5, 5, 0, 0, res_vec);

		cout << res_vec[0] << "  " << res_vec[1] << "  " << res_vec[2] << "  " << res_vec[3] << "  " << res_vec[4]
			<< "  " << res_vec[5] << "  " << res_vec[6] << "  " << res_vec[7] << endl;

	}
		
	getch();

}



*/