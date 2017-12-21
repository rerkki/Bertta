#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include "serialcomm.h"
#include "mainloop.h"
#include <windows.h>
#include <iostream>
#include <fstream>

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

	cout << q_ << endl;

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
	cout << val << endl;
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

/*
int main() {

	lauda_switch_mode(9, 1, 1);

	getch();

}
*/


