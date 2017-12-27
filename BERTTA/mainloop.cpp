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


// Function to call Mettler balance, returns weight in grams
__declspec(dllexport) double mettler(int port, int msg) {

	char * msg_;
	char mettler_str[50] = { 0 };
	string val;
	int msglen;

	if (msg == 1) msg_ = "S\r\n";
	
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

//muutetaan: palauttaa rpm_arvon (int)
//samanlainen funktio momentille
//__declspec(dllexport) void heidolph(int port, int speed, char * output) {
__declspec(dllexport) void heidolph(int port, int speed) {

	char rpm_[7] = { 0 };
	stirr(speed, rpm_);
	read(port, 4, rpm_); 
	Sleep(60);
	
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

	if (dev1 == 1) params[0] = mettler(port1, 1);
	if (dev1 == 2) params[0] = hei_query(port1, 1);
	if (dev1 == 3) params[0] = hei_query(port1, 2);
	if (dev1 == 4) params[0] = lauda_tex(port1);
	if (dev1 == 5) params[0] = lauda_tin(port1);
	if (dev1 == 0) params[0] = 0;

	if (dev2 == 1) params[1] = mettler(port2, 1);
	if (dev2 == 2) params[1] = hei_query(port2, 1);
	if (dev2 == 3) params[1] = hei_query(port2, 2);
	if (dev2 == 4) params[1] = lauda_tex(port2);
	if (dev2 == 5) params[1] = lauda_tin(port2);
	if (dev2 == 0) params[1] = 0;

	if (dev3 == 1) params[2] = mettler(port3, 1);
	if (dev3 == 2) params[2] = hei_query(port3, 1);
	if (dev3 == 3) params[2] = hei_query(port3, 2);
	if (dev3 == 4) params[2] = lauda_tex(port3);
	if (dev3 == 5) params[2] = lauda_tin(port3);
	if (dev3 == 0) params[2] = 0;

	if (dev4 == 1) params[3] = mettler(port4, 1);
	if (dev4 == 2) params[3] = hei_query(port4, 1);
	if (dev4 == 3) params[3] = hei_query(port4, 2);
	if (dev4 == 4) params[3] = lauda_tex(port4);
	if (dev4 == 5) params[3] = lauda_tin(port4);
	if (dev4 == 0) params[3] = 0;

	if (dev5 == 1) params[4] = mettler(port5, 1);
	if (dev5 == 2) params[4] = hei_query(port5, 1);
	if (dev5 == 3) params[4] = hei_query(port5, 2);
	if (dev5 == 4) params[4] = lauda_tex(port5);
	if (dev5 == 5) params[4] = lauda_tin(port5);
	if (dev5 == 0) params[4] = 0;

	if (dev6 == 1) params[5] = mettler(port6, 1);
	if (dev6 == 2) params[5] = hei_query(port6, 1);
	if (dev6 == 3) params[5] = hei_query(port6, 2);
	if (dev6 == 4) params[5] = lauda_tex(port6);
	if (dev6 == 5) params[5] = lauda_tin(port6);
	if (dev6 == 0) params[5] = 0;

	if (dev7 == 1) params[6] = mettler(port7, 1);
	if (dev7 == 2) params[6] = hei_query(port7, 1);
	if (dev7 == 3) params[6] = hei_query(port7, 2);
	if (dev7 == 4) params[6] = lauda_tex(port7);
	if (dev7 == 5) params[6] = lauda_tin(port7);
	if (dev7 == 0) params[6] = 0;

	if (dev8 == 1) params[7] = mettler(port8, 1);
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
	   MReadRS232(9, 1, 9, 2, 13, 3, 13, 4, 10, 5, 11, 5, 12, 5, 0, 0, res_vec);

		cout << res_vec[0] << "  " << res_vec[1] << "  " << res_vec[2] << "  " << res_vec[3] << "  " << res_vec[4]
			<< "  " << res_vec[5] << "  " << res_vec[6] << "  " << res_vec[7] << endl;

	}
		
	getch();

}


*/
