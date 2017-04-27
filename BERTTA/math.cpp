#include <stdio.h>
#include <conio.h>
#include <iomanip>
//#include <algorithm>
#include "sqlite3.h"
#include "serialcomm.h"
#include "mainloop.h"
#include <windows.h>
#include <ctime>

__declspec(dllexport) void rpm(int speed, char * newRpm) {

	char buffer[4]={0};

	int msglen = 1;
	itoa(speed, buffer, 10);
	if (speed>9) msglen = 2;
	if(speed>99) msglen = 3;
	if (speed>999) msglen = 4;
	newRpm[0] = 'R';
	for(int i=0;i<msglen;i++) newRpm[i+1] = buffer[i];
	newRpm[msglen + 1] = '\r';
	newRpm[msglen + 2] = '\n';

//	cout << newRpm << endl;
}


__declspec(dllexport) void pump(float speed_, char * newPump) {

	char buffer[5] = { 0 };
	char buff[5] = { 0 };

	sprintf(buffer, "%.0f", speed_*100);

//	cout << buffer << endl;

	if (speed_ < 100) {

		newPump[0] = '1';
		newPump[1] = 'S';
		newPump[2] = '0';
		newPump[3] = '0';
		newPump[4] = buffer[0];
		newPump[5] = buffer[1];
		newPump[6] = buffer[2];
		newPump[7] = buffer[3];
		newPump[8] = '\r';
		newPump[9] = '\n';
	}

	if (speed_ < 10) {

		newPump[0] = '1';
		newPump[1] = 'S';
		newPump[2] = '0';
		newPump[3] = '0';
		newPump[4] = '0';
		newPump[5] = buffer[0];
		newPump[6] = buffer[1];
		newPump[7] = buffer[2];
		newPump[8] = '\r';
		newPump[9] = '\n';
	}

	if (speed_ < 1) {

		newPump[0] = '1';
		newPump[1] = 'S';
		newPump[2] = '0';
		newPump[3] = '0';
		newPump[4] = '0';
		newPump[5] = '0';
		newPump[6] = buffer[0];
		newPump[7] = buffer[1];
		newPump[8] = '\r';
		newPump[9] = '\n';
	}


	if (speed_ >= 100) {

		newPump[0] = '1';
		newPump[1] = 'S';
		newPump[2] = '0';
		newPump[3] = buffer[0];
		newPump[4] = buffer[1];
		newPump[5] = buffer[2];
		newPump[6] = buffer[3];
		newPump[7] = buffer[4];
		newPump[8] = '\r';
		newPump[9] = '\n';
	}

//	cout << newPump << endl;
}


__declspec(dllexport) void temp(float temp_, char * newTemp) {

	char buffer[5]={0};

	int msglen = 4;

	if(temp_>=100) msglen = 5;

	sprintf(buffer, "%.1f", temp_);
	
	if(msglen==4) {

		newTemp[0] = 'O';
		newTemp[1] = 'U';
		newTemp[2] = 'T';
		newTemp[3] = '_';
		newTemp[4] = 'S';
		newTemp[5] = 'P';
		newTemp[6] = '_';
		newTemp[7] = '0';
		newTemp[8] = '0';
		newTemp[9] = '_';
		newTemp[10] = '0';
		newTemp[11] = buffer[0];
		newTemp[12] = buffer[1];
		newTemp[13] = buffer[2];
		newTemp[14] = buffer[3];
		newTemp[15] = '\r';
		newTemp[16] = '\n';
	}

	if (msglen == 5) {

		newTemp[0] = 'O';
		newTemp[1] = 'U';
		newTemp[2] = 'T';
		newTemp[3] = '_';
		newTemp[4] = 'S';
		newTemp[5] = 'P';
		newTemp[6] = '_';
		newTemp[7] = '0';
		newTemp[8] = '0';
		newTemp[9] = '_';
		newTemp[10] = buffer[0];
		newTemp[11] = buffer[1];
		newTemp[12] = buffer[2];
		newTemp[13] = buffer[3];
		newTemp[14] = buffer[4];
		newTemp[15] = '\r';
		newTemp[16] = '\n';
	}

//	cout << newTemp << endl;
//	cout << strlen(newTemp) << endl;
//	getch();
}






__declspec(dllexport) long int millisec() {

//	long unsigned int sysTime = time(0);
//	long unsigned int sysTimeMS = sysTime * 1000;

//	return sysTimeMS;

	SYSTEMTIME time;
	GetSystemTime(&time);
	LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;

	return time_ms;

}

__declspec(dllexport) void elapsed(long int last_time, long int * params) {

	long int time_now = millisec();

	long int elapsed_ = time_now - last_time;

		params[0] = elapsed_;
		params[1] = time_now;	

}


__declspec(dllexport) double Compute_PID(double timeChange, double errSum, double lastErr, double Input, double Setpoint, double kp, double ki, double kd)
{

	if (timeChange <= 0) timeChange = 1;

	/*Compute all the working error variables*/
	double error = Setpoint - Input;
	errSum += (error * timeChange);
	double dErr = (error - lastErr) / timeChange;

	/*Compute PID Output*/
	double Output = kp * error + ki * errSum + kd * dErr;

	/*Remember some variables for next time*/
	lastErr = error;

	// Output for Lauda
	double Output_ = Setpoint + Output/10;

	if (Output_ > 70) Output_ = 70;
	if (Output_ < 20) Output_ = 20;

	return Output_;
}

