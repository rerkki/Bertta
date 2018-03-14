#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <math.h>
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
//
//	if (speed < 200) speed = 200;

	char buffer[4] = { 0 };

	int msglen = 1;
	itoa(speed, buffer, 10);
	
	if (speed > 0) {
		msglen = 1;
		newRpm[0] = 'R';
		newRpm[1] = '0';
		newRpm[2] = '0';
		newRpm[3] = '0';
		newRpm[4] = buffer[4];
	}

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

//	if (speed < 60) newRpm = "R0001\r\n";

//	cout << newRpm << endl;
}

__declspec(dllexport) void pump2(int enable, float speed_, char * newPump) {

	if (enable == 0) speed_ = 0;

	char buffer[5] = { 0 };
	char buff[5] = { 0 };

	sprintf(buffer, "%.0f", speed_ * 100);

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

	int msglen = 3;

	if (temp_ >= 100) msglen = 5;
	if (temp_ >= 10) msglen = 4;

	sprintf(buffer, "%.1f", temp_);

	if (msglen == 3) {

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
		newTemp[11] = '0';
		newTemp[12] = buffer[0];
		newTemp[13] = buffer[1];
		newTemp[14] = buffer[2];
		newTemp[15] = '\r';
		newTemp[16] = '\n';
	}
	
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

__declspec(dllexport) void time_delay(int start, long int delay, long int start_time, long int start_, long int * params) {

	time_t seconds;

	long int seconds_;

	seconds = time(NULL);

	seconds_ = long int(seconds);

	if (start == 0) {
		params[0] = seconds_;
		params[1] = 0;
		params[2] = 0;
	}

	if (start == 1 || start_ == 1) {
		params[0] = start_time;
		params[1] = 1;
		params[2] = 1;
		if (seconds_ - start_time > delay) {
			params[0] = seconds_;
			params[1] = 0;
			params[2] = 0;
		}
	}

}

__declspec(dllexport) void pump_control(int enable, double amount, double target, long int time_limit, long int start_time, long int * params) {

	time_t seconds;

	long int seconds_;

	long int target_control = 0;

	if (time_limit == 0 || isnan(double(time_limit))) time_limit = 1;
	if (target == 0 || isnan(double(target))) target = 1;
	if (amount == 0 || isnan(double(amount))) target = 0;

	seconds = time(NULL);

	seconds_ = long int(seconds);

	long int time_elapsed = seconds_ - start_time;

	long int weightcontrol = 100 * (amount / target); //paljonko täytyy vielä pumpata

	long int timecontrol = 100 * (time_elapsed) / (time_limit * 60); // paljonko on aikaa kulunut

	if (enable == 0) {
		params[0] = seconds_;
		params[1] = 0;
		params[2] = 0;
		params[3] = 0;
		params[4] = 0;
	}

	if (100 * (double(weightcontrol) / double(timecontrol)) < 70) target_control = 1;

	if (enable == 1) {
		params[0] = start_time;
		params[1] = time_elapsed;
		params[2] = timecontrol;
		params[3] = weightcontrol;
		params[4] = target_control;
	}

}

__declspec(dllexport) void start_time(int enable, long int start_time, long int * params) {

	time_t seconds;

	long int seconds_;

	seconds = time(0);

	seconds_ = long int(seconds);

	if (start_time == 0) start_time = seconds_;

	if (enable == 0) params[0] = seconds_;

	if (enable == 1) params[0] = start_time;
}

__declspec(dllexport) void fr_ctrl(int enable, int reset, long int last_time, long int elapsed_last, double target, double amount, double amount_last, long int * params) {

	elapsed_sec(enable, reset, last_time, elapsed_last, params);

	long int elapsed = params[2];

	if (elapsed == 0) elapsed = 1;

	double fr_actual;

	fr_actual = (amount) * 60 / (elapsed);

	params[3] = long int(fr_actual*1000);

	params[4] = long int(target *1000/ fr_actual);

	if(amount > 0) params[5] = long int(amount * 1000);

	if (amount <= 0) params[5] = long int(amount_last * 1000);

	params[6] = long int(fr_actual * 1000);

}

__declspec(dllexport) void elapsed_sec(int enable, int reset, long int last_time, long int elapsed_last,  long int * params) {

	time_t seconds;

	long int seconds_;

	seconds = time(NULL);

	seconds_ = long int(seconds);

	if (last_time == 0) last_time = seconds_;

	if (enable == 0) {
		params[0] = seconds_;
		params[1] = 0;
		params[2] = elapsed_last;

	}

	if (enable == 1) {
		params[0] = seconds_;
		params[1] = seconds_ - last_time;
		params[2] = elapsed_last + params[1];
	}

	if (reset > 0) {
		params[0] = 0;
		params[1] = 0;
		params[2] = 0;
	}
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

	double treshold_ = 0.5*abs(Tset - Tcurrent) + 0.5*treshold/10000;

	params[0] = int(treshold_ * 10000);
	params[1] = 0;
	if (treshold_ < 1) {
		params[1] = 1; 
	}

}

__declspec(dllexport) void pump_amount4(int master, int pause, int reset, int count, int manual, double fr_manual, double scale, double elapsed, double step_previous, double amount_step_previous, double * target, double * time_, double * params) {

	double step = 0;
	double fr = 0;
	double amount_step = 0;
	double elapsed_step = 0;
	double reset_out = 1;
	double time_step = 0;
	double target_step = 0;
	double time_to_target = 0;
	double frc = 0;
	double pumpCtrl = 100;

	double STEPTARGET = 0; // for process page only
	double TOTALTARGET = 0; // for process page only

	double target_step0 = target[0];
	double target_step1 = target[0] + target[1];
	double target_step2 = target[0] + target[1] + target[2];
	double target_step3 = target[0] + target[1] + target[2] + target[3];
	double target_step4 = target[0] + target[1] + target[2] + target[3] + target[4];
	double target_step5 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5];
	double target_step6 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6];
	double target_step7 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7];
	double target_step8 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7] + target[8];
	double target_step9 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7] + target[8] + target[9];
	TOTALTARGET = target_step9;

	double amount = -1 * scale;

	if (step == 11) step = 0;

	if (amount <= target_step9 && time_[9] > 0) { step = 9; fr = target[9] / time_[9]; time_step = time_[9]; target_step = target_step9; STEPTARGET = target[9];}
	if (amount <= target_step8 && time_[8] > 0) { step = 8; fr = target[8] / time_[8]; time_step = time_[8]; target_step = target_step8; STEPTARGET = target[8];}
	if (amount <= target_step7 && time_[7] > 0) { step = 7; fr = target[7] / time_[7]; time_step = time_[7]; target_step = target_step7; STEPTARGET = target[7];}
	if (amount <= target_step6 && time_[6] > 0) { step = 6; fr = target[6] / time_[6]; time_step = time_[6]; target_step = target_step6; STEPTARGET = target[6];}
	if (amount <= target_step5 && time_[5] > 0) { step = 5; fr = target[5] / time_[5]; time_step = time_[5]; target_step = target_step5; STEPTARGET = target[5];}
	if (amount <= target_step4 && time_[4] > 0) { step = 4; fr = target[4] / time_[4]; time_step = time_[4]; target_step = target_step4; STEPTARGET = target[4];}
	if (amount <= target_step3 && time_[3] > 0) { step = 3; fr = target[3] / time_[3]; time_step = time_[3]; target_step = target_step3; STEPTARGET = target[3];}
	if (amount <= target_step2 && time_[2] > 0) { step = 2; fr = target[2] / time_[2]; time_step = time_[2]; target_step = target_step2; STEPTARGET = target[2];}
	if (amount <= target_step1 && time_[1] > 0) { step = 1; fr = target[1] / time_[1]; time_step = time_[1]; target_step = target_step1; STEPTARGET = target[1];}
	if (amount <= target_step0 && time_[0] > 0) { step = 0; fr = target[0] / time_[0]; time_step = time_[0]; target_step = target_step0; STEPTARGET = target[0];}
		

		if (step > 0) amount_step = amount - amount_step_previous;

		if (step == 0) {
			amount_step = amount;
			amount_step_previous = 0;
		}

		elapsed_step = elapsed;

		if (master == 0) fr = 0;
		if (pause == 0) fr = 0;

		if (reset == 1) {
			step = 0; amount = 0;
		}

		if (amount >= target_step9) {
			step = 10; fr = 0;
		}

		frc = fr;

		if (elapsed < time_step * 60 && amount_step < STEPTARGET) frc = (STEPTARGET - amount_step) / ((time_step * 60 - elapsed) / 60);
//		if (elapsed < time_step * 60 && amount_step < target_step) frc = (target_step - amount_step) / ((time_step * 60 - elapsed) / 60);
		if (frc > 1.8*fr) frc = 1.8*fr;
		if (frc < 0.2*fr) frc = 0.2*fr;
		fr = frc;

		if (step > step_previous) {
			reset_out = 0;
			fr = 0;
			amount_step_previous += amount_step;
			amount_step = 0;
			elapsed_step = 0;
		}

//		time_to_target = 60*(target_step - amount_step)/(target_step/time_step);
		time_to_target = 60 * (STEPTARGET - amount_step) / (STEPTARGET / time_step);
		
		if (time_to_target < 10) fr = 0.3*fr;

		if (time_to_target >  0) pumpCtrl = (time_step*60 - elapsed)*100/time_to_target;

		if (target_step == 0) fr = 0;

	
		if (manual == 1) {
			step = 11;
			fr = fr_manual;
			amount_step = 0;
		}


	params[0] = fr;
	params[1] = step;
	params[2] = amount;
	params[3] = count + 1;
	params[4] = amount_step;
	if (manual == 0) params[5] = elapsed_step;
	if (manual == 1) params[5] = 0;
	if (manual == 0 && elapsed_step > 0) params[6] = amount_step / (elapsed_step / 60); // flow rate
	if (manual == 0 && elapsed_step == 0) params[6] = 0; // flow rate
	if (manual == 1) params[6] = fr;
	params[7] = reset_out;
	params[8] = amount_step_previous; // bookkeeping of previous step amounts
	if (manual == 0) params[9] = time_to_target;
	if (manual == 1) params[9] = 0;
	params[10] = STEPTARGET;
	params[11] = TOTALTARGET;
	params[12] = pumpCtrl;

}

__declspec(dllexport) void pump_amount3(int master, int pause, int reset, int count, int manual, double fr_manual, double scale, double * target, double * time_, double * params) {

	double step = 0;
	double fr = 0;

	double target_step0 = target[0];
	double target_step1 = target[0] + target[1];
	double target_step2 = target[0] + target[1] + target[2];
	double target_step3 = target[0] + target[1] + target[2] + target[3];
	double target_step4 = target[0] + target[1] + target[2] + target[3] + target[4];
	double target_step5 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5];
	double target_step6 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6];
	double target_step7 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7];
	double target_step8 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7] + target[8];
	double target_step9 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7] + target[8] + target[9];

	double amount = -1 * scale;

	if (amount <= target_step9 && time_[9] > 0) { step = 9; fr = target[9] / time_[9]; }
	if (amount <= target_step8 && time_[8] > 0) { step = 8; fr = target[8] / time_[8]; }
	if (amount <= target_step7 && time_[7] > 0) { step = 7; fr = target[7] / time_[7]; }
	if (amount <= target_step6 && time_[6] > 0) { step = 6; fr = target[6] / time_[6]; }
	if (amount <= target_step5 && time_[5] > 0) { step = 5; fr = target[5] / time_[5]; }
	if (amount <= target_step4 && time_[4] > 0) { step = 4; fr = target[4] / time_[4]; }
	if (amount <= target_step3 && time_[3] > 0) { step = 3; fr = target[3] / time_[3]; }
	if (amount <= target_step2 && time_[2] > 0) { step = 2; fr = target[2] / time_[2]; }
	if (amount <= target_step1 && time_[1] > 0) { step = 1; fr = target[1] / time_[1]; }
	if (amount <= target_step0 && time_[0] > 0) { step = 0; fr = target[0] / time_[0]; }

	if (master == 0) fr = 0;
	if (pause == 0) fr = 0;
	if (reset == 1) {
		step = 0; amount = 0;
	}

	if (amount >= target_step9) {
		step = 10; fr = 0;
	}

	if (manual == 1) {
		step = 10;
		fr = fr_manual;
	}

	if (fr > 6 && count == 3) {
		fr = 0;
		count = 0;
	}

	params[0] = fr;
	params[1] = step;
	params[2] = amount;
	params[3] = count + 1;




}

__declspec(dllexport) void pump_amount2(int master, int pause, int reset, int count, int manual, double fr_manual, double scale, double elapsed, double * target, double * time_, double * params) {

	//KORJAA previous step ja pumpun pysäytys stepin vaihtuessa siten että steppi ei heti vaihdu!!!!
	double step = 0;
	double fr = 0;
	double amount_step = 0;
	double elapsed_step = 0;
	
	double target_step0 = target[0];
	double target_step1 = target[0] + target[1];
	double target_step2 = target[0] + target[1] + target[2];
	double target_step3 = target[0] + target[1] + target[2] + target[3];
	double target_step4 = target[0] + target[1] + target[2] + target[3] + target[4];
	double target_step5 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5];
	double target_step6 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6];
	double target_step7 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7];
	double target_step8 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7] + target[8];
	double target_step9 = target[0] + target[1] + target[2] + target[3] + target[4] + target[5] + target[6] + target[7] + target[8] + target[9];

	double amount = -1 * scale;

	if (amount <= target_step9 && time_[9] > 0) { step = 9; fr = target[9] / time_[9]; }
	if (amount <= target_step8 && time_[8] > 0) { step = 8; fr = target[8] / time_[8]; }
	if (amount <= target_step7 && time_[7] > 0) { step = 7; fr = target[7] / time_[7]; }
	if (amount <= target_step6 && time_[6] > 0) { step = 6; fr = target[6] / time_[6]; }
	if (amount <= target_step5 && time_[5] > 0) { step = 5; fr = target[5] / time_[5]; }
	if (amount <= target_step4 && time_[4] > 0) { step = 4; fr = target[4] / time_[4]; }
	if (amount <= target_step3 && time_[3] > 0) { step = 3; fr = target[3] / time_[3]; }
	if (amount <= target_step2 && time_[2] > 0) { step = 2; fr = target[2] / time_[2]; }
	if (amount <= target_step1 && time_[1] > 0) { step = 1; fr = target[1] / time_[1]; }
	if (amount <= target_step0 && time_[0] > 0) { step = 0; fr = target[0] / time_[0]; }

	if (step == 9) amount_step = amount - target_step8 - target_step7 - target_step6 - target_step5 - target_step4 - target_step3 - target_step2 - target_step1 - target_step0;
	if (step == 8) amount_step = amount - target_step7 - target_step6 - target_step5 - target_step4 - target_step3 - target_step2 - target_step1 - target_step0;
	if (step == 7) amount_step = amount - target_step6 - target_step5 - target_step4 - target_step3 - target_step2 - target_step1 - target_step0;
	if (step == 6) amount_step = amount - target_step5 - target_step4 - target_step3 - target_step2 - target_step1 - target_step0;
	if (step == 5) amount_step = amount - target_step4 - target_step3 - target_step2 - target_step1 - target_step0;
	if (step == 4) amount_step = amount - target_step3 - target_step2 - target_step1 - target_step0;
	if (step == 3) amount_step = amount - target_step2 - target_step1 - target_step0;
	if (step == 2) amount_step = amount - target_step1 - target_step0;
	if (step == 1) amount_step = amount - target_step0;
	if (step == 0) amount_step = amount;

	if (step == 9) elapsed_step = elapsed;// -60 * (time_[8] + time_[7] + time_[6] + time_[5] + time_[4] + time_[3] + time_[2] + time_[1] + time_[0]);
	if (step == 8) elapsed_step = elapsed;// -60 * (time_[7] + time_[6] + time_[5] + time_[4] + time_[3] + time_[2] + time_[1] + time_[0]);
	if (step == 7) elapsed_step = elapsed;// -60 * (time_[6] + time_[5] + time_[4] + time_[3] + time_[2] + time_[1] + time_[0]);
	if (step == 6) elapsed_step = elapsed;// -60 * (time_[5] + time_[4] + time_[3] + time_[2] + time_[1] + time_[0]);
	if (step == 5) elapsed_step = elapsed;// -60 * (time_[4] + time_[3] + time_[2] + time_[1] + time_[0]);
	if (step == 4) elapsed_step = elapsed;// -60 * (time_[3] + time_[2] + time_[1] + time_[0]);
	if (step == 3) elapsed_step = elapsed;// -60 * (time_[2] + time_[1] + time_[0]);
	if (step == 2) elapsed_step = elapsed;// -60 * (time_[1] + time_[0]);
	if (step == 1) elapsed_step = elapsed;// -60 * (time_[0]);
	if (step == 0) elapsed_step = elapsed;

	if (master == 0) fr = 0;
	if (pause == 0) fr = 0;
	if (reset == 1) {
		step = 0; amount = 0;
	}

	if (amount >= target_step9) {
		step = 10; fr = 0;
	}

	if (manual == 1) {
		step = 10;
		fr = fr_manual;
	}

	if (fr > 6 && count == 3) {
		fr = 0;
		count = 0;
	}

	params[0] = fr;
	params[1] = step;
	params[2] = amount;
	params[3] = count + 1;
	params[4] = amount_step;
	params[5] = elapsed_step;
	params[6] = amount_step / (elapsed_step/60); // flow rate




}

__declspec(dllexport) void pump_amount(int enable, int reset, double target, double bal, long int bal_previous, long int bal_start, long int step, long int * params){

	if (reset == 1) {
		enable = 0;
		step = 0;
		bal = 0;
		bal_previous = 0;
		target = 0;
		params[0] = 0;
		params[1] = 0;
		params[2] = 0;
		params[3] = 0;
		params[4] = 0;
		params[5] = 0;
	}

	if (enable == 0) {
		params[3] = step; //uusi korjaus 2208
		params[0] = bal_previous;
		if(params[0]==0) params[0] = long int(bal * 100);
		params[1] = 0;
		params[2] = bal_previous - long int(bal * 100);
		params[4] = 0;
		params[5] = bal_previous;
	}
	//korjaa...
	if (step == 10) {
		enable = 0;
		params[0] = long int(bal * 100);
		params[1] = 0;
		params[2] = 0;
		params[3] = 10; //3 ?????
		params[4] = 0;
		params[5] = bal_start;
	}


	if (long int(target * 100) - (bal_previous - long int(bal * 100)) < 1 && step < 10) {
		enable = 0;
		step += 1;
		params[0] = long int(bal * 100);
		params[1] = 1;
		params[2] = 0;
		params[4] = 0;
		params[5] = bal_start;
	}

	if (enable == 1) {
		params[0] = bal_previous;
		params[1] = 0;
		params[2] = bal_previous - long int(bal * 100);
		params[4] = 1;
		params[5] = bal_start;
	}

	if (enable == 1 && step==0) {
		params[0] = bal_previous;
		params[1] = 0;
		params[2] = bal_previous - long int(bal * 100);
		params[4] = 1;
		params[5] = bal_start;
	}

	params[3] = step;

}

__declspec(dllexport) double hold(int enable, double in1, double in2) {

	double retval = in1;

	if (enable == 1) {

		if (in1 >= 0) retval = in2;
	}

	return retval;
}

__declspec(dllexport) double hold3(int enable, double in1, double in2) {

	double retval = in1;

	if (enable == 1) {

		if (in1 >= 0) retval = in2;
	}

	return retval;
}

__declspec(dllexport) void hold2(int enable, double in1, double in2, double count, double * params) { // double in2) {

	double retval = in1;
	params[1] = 0;

	if (enable == 1) {
		if (in1 >= 0.5) retval = in2;
		count += 1;
	}

	if (count >= 3) params[1] = 1;

	//return retval;

	params[0] = retval;
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

__declspec(dllexport) void t_ramp3(int master, int pause, int shutdown, int Tr_or_Tj, double Tr, double Tr_last, long int elapsed, double step_previous, double * SeqParams, long int * TimeParams, double * params) {

	double Tinit_0 = SeqParams[0];
	double Tinit_1 = SeqParams[1];
	double Tinit_2 = SeqParams[2];
	double Tinit_3 = SeqParams[3];
	double Tinit_4 = SeqParams[4];

	double Tset_0 = SeqParams[5];
	double Tset_1 = SeqParams[6];
	double Tset_2 = SeqParams[7];
	double Tset_3 = SeqParams[8];
	double Tset_4 = SeqParams[9];

	double Fail_0 = SeqParams[10];
	double Fail_1 = SeqParams[11];
	double Fail_2 = SeqParams[12];
	double Fail_3 = SeqParams[13];
	double Fail_4 = SeqParams[14];

	double Tmanual = SeqParams[15];
	double Treshold = SeqParams[16];
	double Xe = SeqParams[17];

	double reset = 0;

	double Tset_ = 0;
	double Tinit_ = 0;
	double T_abs_max = 199;
	double T_abs_min = 20;

	long int Time_0 = TimeParams[0] * 60;
	long int Time_1 = TimeParams[1] * 60;
	long int Time_2 = TimeParams[2] * 60;
	long int Time_3 = TimeParams[3] * 60;
	long int Time_4 = TimeParams[4] * 60;
	long int Time_ = 0;

	double step = step_previous; // virhettä...

	if (step == 0) {
		Tset_ = Tset_0;
		Tinit_ = Tinit_0;
	}

	if (step == 1) {
		Tset_ = Tset_0;
		Tinit_ = Tinit_0;
		if (elapsed - Time_0 > 0) {
			Tset_ = Tset_1;
			Tinit_ = Tinit_1;
		}
	}

	if (step == 2) {
		Tset_ = Tset_1;
		Tinit_ = Tinit_1;
		if (elapsed - Time_1 > 0) {
			Tset_ = Tset_2;
			Tinit_ = Tinit_2;
		}
	}

	if (step == 3) {
		Tset_ = Tset_2;
		Tinit_ = Tinit_2;
		if (elapsed - Time_2 > 0) {
			Tset_ = Tset_3;
			Tinit_ = Tinit_3;
		}
	}

	if (step == 4) {
		Tset_ = Tset_3;
		Tinit_ = Tinit_3;
		if (elapsed - Time_3 > 0) {
			Tset_ = Tset_4;
			Tinit_ = Tinit_4;
		}
	}

	if (step == 4) {
		Tset_ = Tset_4;
		Tinit_ = Tinit_4;
		if (elapsed - Time_4 > 0) {
			Tset_ = 20;
			Tinit_ = Tset_4;
		}
	}


	if (abs(Tset_0 - Tr) < Treshold && step == 0) {
		step = 1;
		reset = 1;
	}

	if (abs(Tset_1 - Tr) < Treshold && step == 1) {
		step = 2;
		reset = 1;
	}

	if (abs(Tset_2 - Tr) < Treshold && step == 2) {
		step = 3;
	}

	if (abs(Tset_3 - Tr) < Treshold && step == 3) {
		step = 4;
	}

	if (abs(Tset_4 - Tr) < Treshold && step == 4) {
		step = 5;
	}


	double Tdiff = 0;
	double slope = 0;
	double intercept = 0;
	if (Tset_ < 199) { slope = 0.445087; intercept = -26.6324; }
	if (Tset_ < 85) { slope = 0.36; intercept = -19.4; }
	if (Tset_ < 70) { slope = 0.2055; intercept = -8.585; }
	if (Tset_ < 50) { slope = 0.0845; intercept = -2.535; }
	if (Tset_ < 30) { slope = 0; intercept = 0; }
	Tdiff = slope*Tset_ + intercept;

	int direction;
	if (Tinit_ > Tset_) direction = 1; //cools down
	if (Tinit_ < Tset_) direction = 0; //heats up

	double setpoint;

	if (direction == 0) {
		setpoint = Tr + 50;
		if (Tr > 0.88 * Tset_) setpoint = (2 * Tset_ - Tr) * Xe + Tdiff;
		if (setpoint > 199) setpoint = 199;
	}

	if (direction == 1) {
		setpoint = Tr - 50;
		if (Tr < 1.1*Tset_) setpoint = (2 * Tset_ - Tr) * Xe + Tdiff;
		if (setpoint < 20) setpoint = 20;
	}

	if (pause == 0 && Tr_or_Tj == 0) setpoint = Tr_last + Tdiff;
	if (pause == 0 && Tr_or_Tj == 1) setpoint = Tr_last;

	if (master == 0) setpoint = 20;

	params[0] = Tr;
	params[1] = setpoint;
	params[2] = reset;
	params[3] = Tinit_;
	params[4] = Tset_;
	params[5] = abs(Tset_ - Tr);
	params[6] = Time_;
	params[7] = step;

}

__declspec(dllexport) void t_ramp4(int master, int pause, int reset, int manual, int shutdown, int Tr_or_Tj, double Tr, double adjust,  double Tr_last, double start_time, double step_previous, double * SeqParams, long int * TimeParams, double * params) {
	
	time_t seconds;

	seconds = time(NULL);

	long int start_time_ = long int(start_time);

	if (master == 0 || pause == 0) {
		start_time_ = seconds;
	}

	long int elapsed = long int(seconds) - long int(start_time);

	double Tinit_0 = SeqParams[0];
	double Tinit_1 = SeqParams[1];
	double Tinit_2 = SeqParams[2];
	double Tinit_3 = SeqParams[3];
	double Tinit_4 = SeqParams[4];

	double Tset_0 = SeqParams[5];
	double Tset_1 = SeqParams[6];
	double Tset_2 = SeqParams[7];
	double Tset_3 = SeqParams[8];
	double Tset_4 = SeqParams[9];

	double Fail_0 = SeqParams[10];
	double Fail_1 = SeqParams[11];
	double Fail_2 = SeqParams[12];
	double Fail_3 = SeqParams[13];
	double Fail_4 = SeqParams[14];

	double Tmanual = SeqParams[15];
	double Treshold = SeqParams[16];
	double Xe = SeqParams[17];

	double T_max = SeqParams[18];
	double T_min = SeqParams[19];
	double Fail_manual = SeqParams[20];

	double Tset_ = 0;
	double Tinit_ = 0;
	double Fail_ = 20;
	double T_abs_max = 199;
	double T_abs_min = -39;

	long int Time_0 = TimeParams[0] * 60;
	long int Time_1 = TimeParams[1] * 60;
	long int Time_2 = TimeParams[2] * 60;
	long int Time_3 = TimeParams[3] * 60;
	long int Time_4 = TimeParams[4] * 60;
	long int Time_ = 0;

	double step = step_previous;

	if (step == 0) {
		Tset_ = Tset_0;
		Tinit_ = Tinit_0;
		Fail_ = Fail_0;
	}

	if (step == 1) {
		Tset_ = Tset_0;
		Tinit_ = Tinit_0;
		Fail_ = Fail_0;
		if (elapsed - Time_0 > 0) {
			Tset_ = Tset_1;
			Tinit_ = Tinit_1;
			Fail_ = Fail_1;
		}
	}

	if (step == 2) {
		Tset_ = Tset_1;
		Tinit_ = Tinit_1;
		Fail_ = Fail_1;
		if (elapsed - Time_1 > 0) {
			Tset_ = Tset_2;
			Tinit_ = Tinit_2;
			Fail_ = Fail_2;
		}
	}

	if (step == 3) {
		Tset_ = Tset_2;
		Tinit_ = Tinit_2;
		Fail_ = Fail_2;
		if (elapsed - Time_2 > 0) {
			Tset_ = Tset_3;
			Tinit_ = Tinit_3;
			Fail_ = Fail_3;
		}
	}

	if (step == 4) {
		Tset_ = Tset_3;
		Tinit_ = Tinit_3;
		Fail_ = Fail_3;
		if (elapsed - Time_3 > 0) {
			Tset_ = Tset_4;
			Tinit_ = Tinit_4;
			Fail_ = Fail_4;
		}
	}

	if (step == 5) {
		Tset_ = Tset_4;
		Tinit_ = Tinit_4;
		Fail_ = Fail_4;
		if (elapsed - Time_4 > 0) {
			Tset_ = 20;
			Tinit_ = Tset_4;
			Fail_ = 20;
		}
	}


	if (abs(Tset_0 - Tr) < Treshold && step == 0) {
		step = 1;
		start_time_ = seconds;
	}

	if (abs(Tset_1 - Tr) < Treshold && step == 1) {
		step = 2;
		start_time_ = seconds;
	}

	if (abs(Tset_2 - Tr) < Treshold && step == 2) {
		step = 3;
		start_time_ = seconds;
	}

	if (abs(Tset_3 - Tr) < Treshold && step == 3) {
		step = 4;
		start_time_ = seconds;
	}

	if (abs(Tset_4 - Tr) < Treshold && step == 4) {
		step = 5;
		start_time_ = seconds;
	}


	double Tdiff = 0;
	double slope = 0;
	double intercept = 0;
	if (manual == 1) Tset_ = Tmanual;
	if (Tset_ < 199) { slope = 0.445087; intercept = -26.6324; }
	if (Tset_ < 85) { slope = 0.36; intercept = -19.4; }
	if (Tset_ < 70) { slope = 0.2055; intercept = -8.585; }
	if (Tset_ < 50) { slope = 0.0845; intercept = -2.535; }
	if (Tset_ < 30) { slope = 0; intercept = 0; }
	Tdiff = slope*Tset_ + intercept;

	int direction;
	if (Tinit_ > Tset_) direction = 1; //cools down
	if (Tinit_ < Tset_) direction = 0; //heats up

	double setpoint;

	if (direction == 0) {
		setpoint = Tr + 50;
	//	if (Tr > 0.88 * Tset_) setpoint = (2 * Tset_ - Tr) * Xe + Tdiff;
		if (Tr > 0.88 * Tset_) setpoint = (2 * Tset_ - Tr) + (Tset_ - Tr) * Xe + Tdiff;
		if (setpoint > 199) setpoint = 199;
	}

	if (direction == 1) {
		setpoint = Tr - 50;
	//	if (Tr < 1.1*Tset_) setpoint = (2 * Tset_ - Tr) * Xe + Tdiff;
		if (Tr < 1.1*Tset_) setpoint = (2 * Tset_ - Tr) + (Tset_ - Tr) * Xe + Tdiff;
		if (setpoint < 20) setpoint = 20;
	}

	if (pause == 0 && Tr_or_Tj == 0) setpoint = Tr_last + Tdiff;
	if (pause == 0 && Tr_or_Tj == 1) setpoint = Tr_last;

	if (manual == 1) {
		if (Tr_or_Tj == 0) setpoint = Tmanual + Tdiff;
		if (Tr_or_Tj == 1) setpoint = Tmanual;
		Fail_ = Fail_manual;
	}

	if (master == 0) setpoint = 20;

	if (setpoint > T_max) setpoint = T_max;
	if (setpoint < T_min) setpoint = T_min;
	if (setpoint > T_abs_max) setpoint = T_abs_max;
	if (setpoint < T_abs_min) setpoint = T_abs_min;



	if (reset == 1) {
		start_time_ = seconds;
		step = 0;
	}

	params[0] = Tr;
	params[1] = setpoint + adjust;
	params[2] = double(elapsed);
	params[3] = Tinit_;
	params[4] = Tset_;
	params[5] = abs(Tset_ - Tr);
	params[6] = double(start_time_);// Time_;
	params[7] = step;

}

__declspec(dllexport) void t_ramp5(int master, int pause, int reset, int manual, int shutdown, int Tr_or_Tj, double Tr, double adjust, double Tr_last, double start_time, double step_previous, double * SeqParams, long int * TimeParams, double * params) {

	time_t seconds;

	seconds = time(NULL);

	//	long int start_time_ = long int(start_time);

	if (master == 0 || pause == 0) {
		start_time = seconds;
	}

	long int elapsed = long int(seconds) - long int(start_time);

	double Tinit_0 = SeqParams[0];
	double Tinit_1 = SeqParams[1];
	double Tinit_2 = SeqParams[2];
	double Tinit_3 = SeqParams[3];
	double Tinit_4 = SeqParams[4];

	double Tset_0 = SeqParams[5];
	double Tset_1 = SeqParams[6];
	double Tset_2 = SeqParams[7];
	double Tset_3 = SeqParams[8];
	double Tset_4 = SeqParams[9];

	double Fail_0 = SeqParams[10];
	double Fail_1 = SeqParams[11];
	double Fail_2 = SeqParams[12];
	double Fail_3 = SeqParams[13];
	double Fail_4 = SeqParams[14];

	double Tmanual = SeqParams[15];
	double Treshold = SeqParams[16];
	double Xe = SeqParams[17];

	double T_max = SeqParams[18];
	double T_min = SeqParams[19];
	double Fail_manual = SeqParams[20];

	double Tset_ = 0;
	double Tinit_ = 0;
	double Fail_ = 20;
	double T_abs_max = 199;
	double T_abs_min = -39;

	long int Time_0 = TimeParams[0] * 60;
	long int Time_1 = TimeParams[1] * 60;
	long int Time_2 = TimeParams[2] * 60;
	long int Time_3 = TimeParams[3] * 60;
	long int Time_4 = TimeParams[4] * 60;
	long int Time_ = 0;

	double step = step_previous;

	int s1 = 0;
	int s2 = 0;
	int s3 = 0;
	int s4 = 0;
	int s5 = 0;

	//pysytään stepin mukaisissa olosuhteissa, kunnes odotusaika on kulunut loppuun
	if (step == 0) {
		Tset_ = Tset_0;
		Tinit_ = Tinit_0;
		Fail_ = Fail_0;
	}

	if (step == 1) {
		Tset_ = Tset_1;
		Tinit_ = Tinit_1;
		Fail_ = Fail_1;
		/*		if (elapsed - Time_0 > 0) {
		Tset_ = Tset_1;
		Tinit_ = Tinit_1;
		Fail_ = Fail_1;
		} */
	}

	if (step == 2) {
		Tset_ = Tset_2;
		Tinit_ = Tinit_2;
		Fail_ = Fail_2;
		/*		if (elapsed - Time_1 > 0) {
		Tset_ = Tset_2;
		Tinit_ = Tinit_2;
		Fail_ = Fail_2;
		} */
	}

	if (step == 3) {
		Tset_ = Tset_3;
		Tinit_ = Tinit_3;
		Fail_ = Fail_3;
		/*		if (elapsed - Time_2 > 0) {
		Tset_ = Tset_3;
		Tinit_ = Tinit_3;
		Fail_ = Fail_3;
		}*/
	}

	if (step == 4) {
		Tset_ = Tset_4;
		Tinit_ = Tinit_4;
		Fail_ = Fail_4;
		/*		if (elapsed - Time_3 > 0) {
		Tset_ = Tset_4;
		Tinit_ = Tinit_4;
		Fail_ = Fail_4;
		} */
	}

	//	if (step == 5) {
	//		Tset_ = Tset_5;
	//		Tinit_ = Tinit_5;
	//		Fail_ = Fail_5;
	/*		if (elapsed - Time_4 > 0) {
	Tset_ = 20;
	Tinit_ = Tset_4;
	Fail_ = 20;
	}*/
	//	}

	//Jos tavoitelämpötila saavutetaan, siirrytään seuraavaan steppiin ja nollataan kello (wait)

	if (abs(Tset_4 - Tr) < Treshold && elapsed - Time_4 > 0 && step == 4) {
		step = 5;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_3 - Tr) < Treshold && elapsed - Time_3 > 0 && step == 3) {
		step = 4;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_2 - Tr) < Treshold && elapsed - Time_2 > 0 && step == 2) {
		step = 3;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_1 - Tr) < Treshold && elapsed - Time_1 > 0 && step == 1) {
		step = 2;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_0 - Tr) < Treshold && elapsed - Time_0 && step == 0) {
		step = 1;
		start_time = seconds;
		elapsed = 0;
	}


	double Tdiff = 0;
	double slope = 0;
	double intercept = 0;
	if (manual == 1) Tset_ = Tmanual;
	if (Tset_ < 199) { slope = 0.445087; intercept = -26.6324; }
	if (Tset_ < 85) { slope = 0.36; intercept = -19.4; }
	if (Tset_ < 70) { slope = 0.2055; intercept = -8.585; }
	if (Tset_ < 50) { slope = 0.0845; intercept = -2.535; }
	if (Tset_ < 30) { slope = 0; intercept = 0; }
	Tdiff = slope*Tset_ + intercept;

	int direction;
	if (Tinit_ > Tset_) direction = 1; //cools down
	if (Tinit_ <= Tset_) direction = 0; //heats up

	double setpoint;

	if (direction == 0) {
		setpoint = Tr + 50;
		//	if (Tr > 0.88 * Tset_) setpoint = (2 * Tset_ - Tr) * Xe + Tdiff;
		if (Tr > 0.88 * Tset_) setpoint = (2 * Tset_ - Tr) + (Tset_ - Tr) * Xe + Tdiff;
		if (setpoint > 199) setpoint = 199;
	}

	if (direction == 1) {
		setpoint = Tr - 50;
		//	if (Tr < 1.1*Tset_) setpoint = (2 * Tset_ - Tr) * Xe + Tdiff;
		if (Tr < 1.1*Tset_) setpoint = (2 * Tset_ - Tr) + (Tset_ - Tr) * Xe + Tdiff;
		if (setpoint < 20) setpoint = 20;
	}

	if (pause == 0 && Tr_or_Tj == 0) setpoint = Tr_last + Tdiff;
	if (pause == 0 && Tr_or_Tj == 1) setpoint = Tr_last;

	if (manual == 1) {
		if (Tr_or_Tj == 0) setpoint = Tmanual + Tdiff;
		if (Tr_or_Tj == 1) setpoint = Tmanual;
		Fail_ = Fail_manual;
	}

	if (master == 0) setpoint = 20;

	
	if (setpoint > T_max) setpoint = T_max;
	if (setpoint < T_min) setpoint = T_min;
	if (setpoint > T_abs_max) setpoint = T_abs_max;
	if (setpoint < T_abs_min) setpoint = T_abs_min;


	if (reset == 1) {
		start_time = seconds;
		step = 0;
	}

	params[0] = Tr;
	params[1] = setpoint + adjust;
	params[2] = double(elapsed);
	params[3] = Tinit_;
	params[4] = Tset_;
	params[5] = abs(Tset_ - Tr);
	params[6] = double(start_time);// Time_;
	params[7] = step;

}

__declspec(dllexport) double flow_pump3(int enable, int manual, double flow, int port) { //this subroutine only for reglo D

	double reglo_signal = 0;
	double rcoeff = 9;

	if (enable == 0 && manual == 0) flow = 0;

		if (port > 0) {
			ismatec(port, rcoeff*flow);
			reglo_signal = rcoeff*flow;
		}

	return reglo_signal;
}


__declspec(dllexport) void flow_pump2(int enable, int manual, double flow, int pump_type, int port, double * pump_ctrl) {

	double analog_signal = 0.004;
	double pam_signal = 0;
	double reglo_signal = 0;
	double rcoeff = 9;
//	if (flow < 0.5) rcoeff = 4;

	if (enable == 0 && manual == 0) flow = 0;
	
	if (pump_type == 0) {
		if (port > 0) {
			ismatec(port, rcoeff*flow);
			reglo_signal = rcoeff*flow;
		}

	}

	if (pump_type == 1) {
		analog_signal = 0.0008*flow + 0.0042;
		if (analog_signal > 0.02) analog_signal = 0.02;
		if (analog_signal < 0.004) analog_signal = 0.004;
	}

	if (pump_type == 2) {
		pam_signal = 1;
	}

	pump_ctrl[0] = analog_signal;
	pump_ctrl[1] = pam_signal;
	pump_ctrl[2] = reglo_signal;

}

__declspec(dllexport) void flow_pump(double flow, int pump_type, int port, double * pump_ctrl) {

	double analog_signal = 0.004;
	double pam_signal = 0;
	double reglo_signal = 0;
	double rcoeff = 8.009;

	if (pump_type == 0) {
		if (port > 0) {
			ismatec(port, rcoeff*flow);
			reglo_signal = rcoeff*flow;
		}

	}

	if (pump_type == 1) {
		analog_signal = 0.0008*flow + 0.0042;
		if (analog_signal > 0.02) analog_signal = 0.02;
		if (analog_signal < 0.004) analog_signal = 0.004;
	}

	if (pump_type == 2) {
		pam_signal = 1;
	}

	pump_ctrl[0] = analog_signal;
	pump_ctrl[1] = pam_signal;
	pump_ctrl[2] = reglo_signal;

}

__declspec(dllexport) void t_ramp2(int res, int enable, int pause, int bypass, int err, double Tinit, double Tset, double Xe, double T_low, double T_up, double Tcurrent, double Tlast, double Tbyp, double Tfail, double Treshold, long int ramp_time, long int elapsed, double sp_old, double step, double reset_last, double count_last, double * params) {

	int direction = 0;
	int reset = int(reset_last);
	int count = int(count_last);
	if (pause == 0) count = 0;
	if (reset_last == 1) reset = 0;
	

	//y = 0,7849x + 8,1867

	double Tset_ = Tset;
	double Tdiff = 0;
	double slope = 0;
	double intercept = 0;
	if (Tset < 120) { slope = 0.445087; intercept = -26.6324; }
	if (Tset < 85) { slope = 0.36; intercept = -19.4; }
	if (Tset < 70) { slope = 0.2055; intercept = -8.585; }
	if (Tset < 50) { slope = 0.0845; intercept = -2.535; }
	if (Tset < 30) { slope = 0; intercept = 0; }
//	if(Tset > 40) Tset_ = (Tset - 8.1867) / 0.7849; 
    Tdiff = slope*Tset + intercept;
	Tset_ = Tset + Tdiff;

	double Tmax = Tcurrent + 50;
	double Tmin = Tcurrent - 50;

	double setpoint = 0;

	if (Tinit > Tset) direction = 1;
	if (Tinit < Tset) direction = 0;
	if (pause == 0) {
		setpoint = Tlast;
		if(Tlast > 40) setpoint = (Tlast - 8.1867) / 0.7849;
	}

	if (pause == 1) {
		if (direction == 0) {
			setpoint = Tmax;
			if(Tcurrent > 0.85 * Tset) setpoint = (2 * Tset - Tcurrent) *Xe + Tdiff;  //
	//		setpoint = Tmax;
	//		if (Tcurrent > 0.75 * Tset_) setpoint = Tmax * 0.75; //0.75 //
	//		if (Tcurrent > 0.85 * Tset_) setpoint = Tset_; //0.85    //
			if (setpoint > Tmax) setpoint = Tmax;
			if (setpoint > 199) setpoint = 199;   
			
		}
		if (direction == 1) {
			setpoint = Tmin;
	//		setpoint = Tset_;
			if (Tcurrent < 1.1*Tset) setpoint = (2 * Tset - Tcurrent) *Xe + Tdiff;
			if (setpoint < Tmin) setpoint = Tmin;
			if (setpoint < 20) setpoint = 20;
		}
	}


//	if (step > 5) setpoint = Tfail;

	if (abs(Tset - Tcurrent) < Treshold && elapsed/60 > ramp_time) {
//		count = 1000;
		reset = 1;
		if(step < 5) step += 1;
	}
	
//	count += 1;

	if (bypass == 1) setpoint = Tbyp; // 2 * (Tbyp - Tcurrent)*Xe;

	if (err == 1) {
		setpoint = Tfail;
		if (Tfail > 40) setpoint = (Tfail - 8.1867) / 0.7849;
	}

	if (setpoint > T_up) setpoint = T_up;
	if (setpoint < T_low) setpoint = T_low;

	if (res == 1) step = 0;

	params[0] = setpoint;
	params[1] = step;
	params[2] = Tcurrent;
	if (pause == 0 && elapsed > 10) params[2] = Tlast;
	params[3] = double(reset);
	params[4] = double(count); //count -parametrin voi poistaa
}

__declspec(dllexport) void t_ramp6(int master, int pause, int reset, int manual, int shutdown, int Tr_or_Tj, double Tr, double adjust, double Tr_last, double start_time, double step_previous, double * SeqParams, long int * TimeParams, double * params) {

	time_t seconds;

	seconds = time(NULL);

	if (master == 0 || pause == 0) {
		start_time = seconds;
	}

	long int elapsed = long int(seconds) - long int(start_time);

	double Tinit_0 = SeqParams[0];
	double Tinit_1 = SeqParams[1];
	double Tinit_2 = SeqParams[2];
	double Tinit_3 = SeqParams[3];
	double Tinit_4 = SeqParams[4];

	double Tset_0 = SeqParams[5];
	double Tset_1 = SeqParams[6];
	double Tset_2 = SeqParams[7];
	double Tset_3 = SeqParams[8];
	double Tset_4 = SeqParams[9];

	double Fail_0 = SeqParams[10];
	double Fail_1 = SeqParams[11];
	double Fail_2 = SeqParams[12];
	double Fail_3 = SeqParams[13];
	double Fail_4 = SeqParams[14];

	double Tmanual = SeqParams[15];
	double Treshold = SeqParams[16];
	double Xe = SeqParams[17];

	double T_max = SeqParams[18];
	double T_min = SeqParams[19];
	double Fail_manual = SeqParams[20];

	double Tset_ = 0;
	double Tinit_ = 0;
	double Fail_ = 20;
	double T_abs_max = 199;
	double T_abs_min = -39;

	long int Time_0 = TimeParams[0] * 60;
	long int Time_1 = TimeParams[1] * 60;
	long int Time_2 = TimeParams[2] * 60;
	long int Time_3 = TimeParams[3] * 60;
	long int Time_4 = TimeParams[4] * 60;
	long int Time_ = 0;

	double step = step_previous;

	int s1 = 0;
	int s2 = 0;
	int s3 = 0;
	int s4 = 0;
	int s5 = 0;

	//pysytään stepin mukaisissa olosuhteissa, kunnes odotusaika on kulunut loppuun
	if (step == 0) {
		Tset_ = Tset_0;
		Tinit_ = Tinit_0;
		Fail_ = Fail_0;
	}

	if (step == 1) {
		Tset_ = Tset_1;
		Tinit_ = Tinit_1;
		Fail_ = Fail_1;
	}

	if (step == 2) {
		Tset_ = Tset_2;
		Tinit_ = Tinit_2;
		Fail_ = Fail_2;
	}

	if (step == 3) {
		Tset_ = Tset_3;
		Tinit_ = Tinit_3;
		Fail_ = Fail_3;
	}

	if (step == 4) {
		Tset_ = Tset_4;
		Tinit_ = Tinit_4;
		Fail_ = Fail_4;
	}

	//Jos tavoitelämpötila saavutetaan, siirrytään seuraavaan steppiin ja nollataan kello (wait)

	if (abs(Tset_4 - Tr) < Treshold && elapsed - Time_4 > 0 && step == 4) {
		step = 5;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_3 - Tr) < Treshold && elapsed - Time_3 > 0 && step == 3) {
		step = 4;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_2 - Tr) < Treshold && elapsed - Time_2 > 0 && step == 2) {
		step = 3;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_1 - Tr) < Treshold && elapsed - Time_1 > 0 && step == 1) {
		step = 2;
		start_time = seconds;
		elapsed = 0;
	}

	if (abs(Tset_0 - Tr) < Treshold && elapsed - Time_0 && step == 0) {
		step = 1;
		start_time = seconds;
		elapsed = 0;
	}


	double Tdiff = 0;
	double slope = 0;
	double intercept = 0;
	if (manual == 1) Tset_ = Tmanual;
	if (Tset_ < 199) { slope = 0.445087; intercept = -26.6324; }
	if (Tset_ < 85) { slope = 0.36; intercept = -19.4; }
	if (Tset_ < 70) { slope = 0.2055; intercept = -8.585; }
	if (Tset_ < 50) { slope = 0.0845; intercept = -2.535; }
	if (Tset_ < 30) { slope = 0; intercept = 0; }
	Tdiff = slope*Tset_ + intercept;

	int direction;
	if (Tinit_ > Tset_) direction = 1; //cools down
	if (Tinit_ <= Tset_) direction = 0; //heats up

	double setpoint;

	if (direction == 0) {
		setpoint = Tr + 50;
		if (Tr + 50 > Tset_) setpoint = Tset_;
		if (setpoint > 199) setpoint = 199;
	}

	if (direction == 1) {
		setpoint = Tr - 50;
		if (Tr - 50 < Tset_) setpoint = Tset_;
		if (setpoint < 20) setpoint = 20;
	}

	if (pause == 0 && Tr_or_Tj == 0) setpoint = Tr_last;
	if (pause == 0 && Tr_or_Tj == 1) setpoint = Tr_last;

	if (manual == 1) {
		if (Tr_or_Tj == 0) setpoint = Tmanual;
		if (Tr_or_Tj == 1) setpoint = Tmanual;
		Fail_ = Fail_manual;
	}

	if (master == 0) setpoint = 20;

	if (setpoint > T_max) setpoint = T_max;
	if (setpoint < T_min) setpoint = T_min;
	if (setpoint > T_abs_max) setpoint = T_abs_max;
	if (setpoint < T_abs_min) setpoint = T_abs_min;

	if (reset == 1) {
		start_time = seconds;
		step = 0;
	}

	params[0] = Tr;
	params[1] = setpoint + adjust;
	params[2] = double(elapsed);
	params[3] = Tinit_;
	params[4] = Tset_;
	params[5] = abs(Tset_ - Tr);
	params[6] = double(start_time);
	params[7] = step;

}

__declspec(dllexport) void rising_edge(int reset, int input, int prev_input, int prev_count, int * params) {

	params[0] = prev_count;
	if (input == 1 && prev_input==0) params[0] = prev_count + 1;
	if (params[0] > 2) params[0] = 2;
	params[1] = input;
	if (reset == 1) {
		params[0] = 0;
		params[1] = 0;
		prev_count = 0;
	}
	
}

__declspec(dllexport) int ramp_test(int last_count) {

	int count = last_count + 1;

	if (count > 10) count = 0;

	return count;

}

__declspec(dllexport) long int time_left(long int rt, long int start_time) {

	time_t seconds;
	long int seconds_;
	seconds = time(NULL);
	seconds_ = long int(seconds);

	return rt - (seconds_ - start_time);

}

__declspec(dllexport) void Compute_PID(double errSum, double lastErr, double last_time, double last_timeChange, double Input, double Setpoint, double kp, double ki, double kd, double * params)
{
	time_t seconds;

	seconds = time(NULL);

	long int timeChange = long int(seconds) - long int(last_time);

	if (timeChange <= 0) timeChange = last_timeChange;

	double error = Setpoint - Input;
	double errSum_ = error * double(timeChange*1000)/1000;
	double dErr = (error - lastErr) / double(timeChange*1000)/1000;

	double Output = kp * error + ki * errSum + kd * dErr;

	if (Output > Input+50) Output = Input+50;
	if (Output < 0) Output = 0;

	lastErr = error;

	params[0] = Output;
	params[1] += errSum_;
	params[2] = lastErr;
	params[3] = double(seconds);
	params[4] = timeChange;

}

__declspec(dllexport) void ramp_simple(int pause, int reset, int master, double elapsed, double time_set, double T0_, double Tr, double Tr_last, double T_sp, double treshold, double * params) {

	double intercept;

	double slope = 0;

//	double T0 = Tr;

	double setpoint;

	if (reset == 1) {

		params[3] = 0;

		params[4] = Tr_last;

		params[0] = Tr;

		setpoint = Tr_last;

	}

	if (pause == 0 && reset==0) {

		params[4] = Tr;

		params[0] = T0_;

		if (time_set > 0) {

			slope = (T_sp - T0_) / time_set;

			intercept = T0_;

			setpoint = slope*(elapsed / 60000) + intercept;
		
		}else setpoint = T_sp;

		if (slope > 0 && setpoint > T_sp) {
			setpoint = T_sp;
		}
		if (slope < 0 && setpoint < T_sp) {
			setpoint = T_sp;
		}
 
	}

	if (pause == 1) {

		if (Tr_last == 0) Tr_last = Tr;

		setpoint = Tr_last;

		if (params[5] == 1) setpoint = T_sp;

		params[4] = Tr_last;

		params[0] = Tr;
		
	}

	if (master == 0) setpoint = 20;

	params[6] = 0;
	if (abs(Tr - T_sp) < treshold) params[6] = 1;

	params[1] = setpoint;

	params[2] = slope;

	params[3] = elapsed / 60000;

}


__declspec(dllexport) void ramp(int pause, int shutdown, int reset, int grad, int manual, double T_man, long int start_time, long int last_time, long int elapsed_total, long int step, double Tr, double treshold, double * Seq, long int * TimeParams, long int * params) {

	if (treshold < 0.5) treshold = 0.5;
	if (treshold > 2) treshold = 2;

	double Sp0 = Seq[0]; double Sp1 = Seq[1]; double Sp2 = Seq[2]; double Sp3 = Seq[3]; double Sp4 = Seq[4];

	double Sp_ = Sp0;
	double Sp0_man;

	long int time0 = TimeParams[0]; long int time1 = TimeParams[1]; long int time2 = TimeParams[2]; long int time3 = TimeParams[3]; long int time4 = TimeParams[4]; long int time_man = TimeParams[5];

	double slope1 = 1;
	double slope2 = 1;
	double slope3 = 1;
	double slope4 = 1;
	double slope_man = 1;

	if (time0>0) slope1 = (Sp1 - Sp0) / (time1 * 60000);
	if (time1>0) slope2 = (Sp2 - Sp1) / (time2 * 60000);
	if (time2>0) slope3 = (Sp3 - Sp2) / (time3 * 60000);
	if (time3>0) slope4 = (Sp4 - Sp3) / (time4 * 60000);

	double intercept1 = Sp0;
	double intercept2 = Sp1;
	double intercept3 = Sp2;
	double intercept4 = Sp3;



	bool timeLimit0 = false;
	bool timeLimit1 = false;
	bool timeLimit2 = false;
	bool timeLimit3 = false;
	bool timeLimit4 = false;

	if (elapsed_total > time0 * 60000) timeLimit0 = true;
	if (elapsed_total > (time0 + time1) * 60000) timeLimit1 = true;
	if (elapsed_total > (time0 + time1 + time2) * 60000) timeLimit2 = true;
	if (elapsed_total > (time0 + time1 + time2 + time3) * 60000) timeLimit3 = true;
	if (elapsed_total > (time0 + time1 + time2 + time3 + time4) * 60000) timeLimit4 = true;

	if (timeLimit0 && step == 0) {
		if (abs(Tr - Sp0) < treshold) {
			step = 1;
		}
		else {
			pause = 1;
		}
	}

	if (timeLimit1 && step == 1) {
		if (abs(Tr - Sp1) < treshold) {
			step = 2;
		}
		else {
			pause = 1;
		}
	}


	if (timeLimit2 && step == 2) {
		if (abs(Tr - Sp2) < treshold) {
			step = 3;
		}
		else {
			pause = 1;
		}
	}


	if (timeLimit3 && step == 3) {
		if (abs(Tr - Sp3) < treshold) {
			step = 4;
		}
		else {
			pause = 1;
		}
	}

	if (timeLimit4 && step == 4) {
		if (abs(Tr - Sp4) < treshold) {
			step = 5;
		}
	}

	if (step == 0 && grad == 0) Sp_ = Sp0;
	if (step == 1 && grad == 0) Sp_ = Sp1;
	if (step == 2 && grad == 0) Sp_ = Sp2;
	if (step == 3 && grad == 0) Sp_ = Sp3;
	if (step == 4 && grad == 0) Sp_ = Sp4;
	if (step == 5 && grad == 0) Sp_ = 20;

	if (step == 0 && grad == 1) Sp_ = Sp0;

	if (step == 1 && grad == 1) {
		Sp_ = (elapsed_total - time0 * 60000)*slope1 + intercept1;
		if (slope1 > 0 && Sp_ > Sp1) Sp_ = Sp1;
		if (slope1 < 0 && Sp_ < Sp1) Sp_ = Sp1;
	}

	if (step == 2 && grad == 1) {
		Sp_ = (elapsed_total - (time0 + time1) * 60000)*slope2 + intercept2;
		if (slope2 > 0 && Sp_ > Sp2) Sp_ = Sp2;
		if (slope2 < 0 && Sp_ < Sp2) Sp_ = Sp2;
	}

	if (step == 3 && grad == 1) {
		Sp_ = (elapsed_total - (time0 + time1 + time2) * 60000)*slope3 + intercept3;
		if (slope3 > 0 && Sp_ > Sp3) Sp_ = Sp3;
		if (slope3 < 0 && Sp_ < Sp3) Sp_ = Sp3;
	}

	if (step == 4 && grad == 1) {
		Sp_ = (elapsed_total - (time0 + time1 + time2 + time3) * 60000)*slope4 + intercept4;
		if (slope4 > 0 && Sp_ > Sp4) Sp_ = Sp4;
		if (slope4 < 0 && Sp_ < Sp4) Sp_ = Sp4;
	}

//	if (manual == 1) Sp_ = T_man;

	//new gradient implementation to manual control
	if(manual==0) Sp0_man = Tr;
	if (manual == 1) {
		Sp0_man = params[5];
		
		if(time_man>0) slope_man = (T_man - Sp0_man) / (time_man * 60000);
		
		Sp_ = T_man;
	}

	if (shutdown == 1) Sp_ = 20;

	params[3] = step;
	params[4] = Sp_ * 1000;
	params[5] = Sp0_man;

	timer_1(pause, reset, start_time, last_time, elapsed_total, params);

}

__declspec(dllexport) void timer_1(int pause, int reset, long int start_time, long int last_time, long int elapsed_total, long int * params) {


	long int seconds = millisec();

	long int elapsed_sec = long int(seconds) - long int(last_time);

	if (last_time > seconds) elapsed_sec = 60000 - last_time + seconds;

	if (pause == 1) {

		start_time = seconds;
		elapsed_sec = 0;

	}

	if (reset == 1) {
		start_time = seconds;
		elapsed_total = 0;
		elapsed_sec = 0;
		last_time = 0;
	}

	params[0] = seconds;
	params[1] = start_time;
	params[2] = elapsed_total + elapsed_sec;

}

