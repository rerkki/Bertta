#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include "sqlite3.h"
#include "serialcomm.h"
#include "mainloop.h"
#include <windows.h>


__declspec(dllexport) void rpm(int speed, char * newRpm) {

	char buffer[4]={0};
	int msglen = 3;
	itoa(speed, buffer, 10);
	if(speed>999) msglen = 4;
	newRpm[0] = 'R';
	for(int i=0;i<msglen;i++) newRpm[i+1] = buffer[i];
	newRpm[msglen + 1] = '\r';
	newRpm[msglen + 2] = '\n';
}

__declspec(dllexport) void temp(float temp_, char * newTemp) {

	char buffer[5]={0};
	int msglen = 4;
	if(temp_>99) msglen = 5;

	sprintf(buffer, "%.1f", temp_);

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
	
	if(msglen==4) {
		
		newTemp[10] = '0';
		newTemp[11] = buffer[0];
		newTemp[12] = buffer[1];
		newTemp[13] = buffer[2];
		newTemp[14] = buffer[3];
		newTemp[15] = '\r';
		newTemp[16] = '\n';
	}
/*
	if(msglen==5) {

		for(int i=0;i<msglen;i++) newTemp[i+1] = buffer[i];
		newTemp[msglen + 1] = '\r';
		newTemp[msglen + 2] = '\n';
	} */
}