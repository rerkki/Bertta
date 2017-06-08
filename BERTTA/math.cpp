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

__declspec(dllexport) void stirr(int speed, char * newRpm) {

	if (speed < 200) speed = 200;

	char buffer[4] = { 0 };

	int msglen = 1;
	itoa(speed, buffer, 10);
	if (speed > 9) {
		msglen = 2;
		newRpm[0] = 'R';
		newRpm[1] = '0';
		newRpm[2] = '0';
		for (int i = 0; i<msglen; i++) newRpm[i + 3] = buffer[i];
	}

	if (speed > 99) {
		msglen = 3;
		newRpm[0] = 'R';
		newRpm[1] = '0';
		for (int i = 0; i<msglen; i++) newRpm[i + 2] = buffer[i];
	}

	if (speed > 999) {
		msglen = 3;
		newRpm[0] = 'R';
		for (int i = 0; i<msglen; i++) newRpm[i + 1] = buffer[i];
	}

	newRpm[5] = '\r';
	newRpm[6] = '\n';

	//if (speed == 0) newRpm = "R0000\r\n";

	cout << newRpm << endl;
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

/*
__declspec(dllexport) void t_ramp2(long int last_time, double DT, long int * params) {

	long int time_now = millisec();

	long int elapsed_ = time_now - last_time;

	params[0] = elapsed_;
	params[1] = time_now;

}
*/
__declspec(dllexport) void elapsed_sec(long int last_time, long int * params) {

	time_t seconds;

	long int seconds_;

	double retval = 0;

	seconds = time(NULL);

	seconds_ = long int(seconds);

	long int elapsed_ = seconds_ - last_time;

	params[0] = elapsed_;
	params[1] = seconds_;


}

__declspec(dllexport) long int t_epoch(int enable, long int start_time) {

	time_t seconds;

	long int seconds_;

	seconds = time(NULL);

	seconds_ = long int(seconds);

	long int elapsed = seconds_ ;

	if(enable==0) return seconds_;
	if (enable > 0) return start_time;
}



__declspec(dllexport) void ramp_timer(int enable, int pause, long int rt, long int start_time, long int pause_time, long int paused, long int paused_old, long int * params) {

	time_t seconds;

	long int seconds_;

	seconds = time(NULL);

	seconds_ = long int(seconds);

	params[0] = 0;// seconds_; //params 0 is the current time...

	if (enable == 1) params[1] = start_time; //this defines the starting moment of the timed ramp
	if (pause == 0) params[2] = seconds_; //params 2 defines the moment (epoch) of pause
	if (pause == 1) params[2] = pause_time;
	if (pause == 1) params[3] = seconds_ - pause_time + paused_old; //params 3 keeps the ramp time (epoch) interrupted during the pause
	if (pause == 0) params[3] = paused; 
	if (pause == 1) params[4] = paused_old; //params 4 keeps track of the pause time during each pause
	if (pause == 0) params[4] = paused;
	params[5] = rt - (seconds_ - start_time) + paused; //params 5 is the total pause time (sum)
	if (params[5] < 0) params[5] = 0;

	//initialization of the time sequences
	if (enable == 0) {
		params[1] = seconds_;
		params[2] = seconds_;
		params[3] = 0;
		params[4] = 0;
		params[5] = 0;
	}

}

__declspec(dllexport) void ramp_watch(int enable, int pause, long int elapsed, long int elapsed_previous, long int elapsed_total, long int * params) {

	if (elapsed < 0) elapsed = elapsed_previous;
	if (elapsed > 5000) elapsed = elapsed_previous;
//	long int elapsed_total = 0;

	if (enable == 1) params[0] = elapsed + elapsed_total;
	if(pause == 1) params[0] = elapsed_total;
	params[1] = elapsed_previous;
}

__declspec(dllexport) void sequencer(double Tset, double Tcurrent, int treshold, int seq_previous, int * params){

	double treshold_ = 0.2*abs(Tset - Tcurrent) + 0.8*treshold/10000;

	params[0] = int(treshold_ * 10000);
	params[1] = 0;
	if (treshold_ < 0.6) {
		params[1] = 1; 
	}

}

__declspec(dllexport) void pump_amount(int enable, double target, double bal, long int bal_previous, long int * params){

	long int amount = 0;


	if (enable == 0) {
		params[0] = long int(bal * 100);
		params[1] = 0;
		params[2] = 0;
//		params[3] = 1;
		
	}

	if (enable == 1) {
		params[0] = bal_previous;
		amount = bal_previous -long int(bal * 100);
		params[2] = amount;
		if (long int(target * 100) - amount < 1) {
			params[1] = 1;
//			params[3] = 0;
		}

		

	}

	
}



__declspec(dllexport) double hold(int enable, double in1, double in2) {

	double retval = in1;

	if (enable == 1) {

		if (in1 == 0) retval = in2;
	}

	return retval;
}

__declspec(dllexport) void seq_count(int in1, int in2, int in3, int in4, int * params) {

	params[0] = in1;
	params[1] = in1 - in2;
	params[2] = in3;
	if (in4 == 1) params[2] += 1;

}

__declspec(dllexport) double t_ramp(int enable, long int ramp_time, long int elapsed, double Tset, double Tcurrent, double Tcurr_prev, int direction) {

	double setpoint = 0;

	if (enable == 1) {
		if (ramp_time <= 0) ramp_time = 10000000;

		double DT = 0;

		DT = (Tset - Tcurrent) / double(ramp_time);

		setpoint = (DT * double(elapsed) / 1000) + Tcurrent;

		if (direction == 0 && setpoint < Tcurrent) setpoint = Tcurr_prev;
		if (direction == 1 && setpoint > Tcurrent) setpoint = Tcurr_prev;
	}
	else setpoint = Tcurrent;

	return setpoint;
}

__declspec(dllexport) double t_ramp2(int enable, int pause, double Tinit, double Tset, double Tcurrent, long int ramp_time, long int elapsed, double sp_old) {

	int direction = 0;

	if (Tinit > Tset) direction = 1;
	if (Tinit < Tset) direction = 0;

	double Tdiff = 8;
	if (direction == 0) {
		if (abs(sp_old - Tset) < 10) Tdiff = 10;
		if (abs(sp_old - Tset) < 3) Tdiff = 1;
	}

	if (direction == 1) {
		if (abs(sp_old - Tset) < 10) Tdiff = 10;
	}



	double DT = (Tset - Tinit) / ramp_time;
	double setpoint = Tinit;

	if (pause == 1) DT = 0;

	if (enable == 1) {
		setpoint = sp_old + DT*elapsed / 1000;
		if (direction == 0) {
			if (Tcurrent > Tset) setpoint = Tset;
			if (setpoint > Tset) setpoint = Tset;
			if (setpoint < sp_old) setpoint = sp_old;
			if (setpoint - Tcurrent > Tdiff) setpoint = sp_old;
		}
		if (direction == 1) {
			if (Tcurrent < Tset) setpoint = Tset;
			if (setpoint < Tset) setpoint = Tset;
			if (setpoint > sp_old) setpoint = sp_old;
			if (Tcurrent - setpoint > Tdiff) setpoint = sp_old;
		}
		
	}
	
	return setpoint;
}

__declspec(dllexport) long int time_left(long int rt, long int start_time) {

	time_t seconds;
	long int seconds_;
	seconds = time(NULL);
	seconds_ = long int(seconds);

	return rt - (seconds_ - start_time);

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

