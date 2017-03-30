#include "serialcomm.h"
#include "sqlite3.h"

void sys_err(char *name) {

    WCHAR ptr[1024];
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        0,
        GetLastError(),
        0,
        //(char *)&ptr,
        ptr,
        1024,
        NULL);
    wcout << endl << "Error " << name << ": " << ptr << endl;
    LocalFree(ptr);
}


__declspec(dllexport) string read(int com_port, int device, char *msg_)
{

    int ch;
	int msglen = strlen(msg_);
	char buffer[50];
	for(int i=0;i<50;i++) buffer[i]=NULL;
	char msg[17];
	for(int i=0;i<17;i++) msg[i]=0;
	strcpy(msg, msg_);

    HANDLE file;
    COMMTIMEOUTS timeouts;
    DWORD read, written;
    DCB port;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;

	LPCWSTR port_name;
	if (com_port==1) port_name = L"\\\\.\\COM1";
	if (com_port==2) port_name = L"\\\\.\\COM2";
	if(com_port==3) port_name = L"\\\\.\\COM3";
	if(com_port==4) port_name = L"\\\\.\\COM4";
	if(com_port==5) port_name = L"\\\\.\\COM5";
	if(com_port==6) port_name = L"\\\\.\\COM6";
	if(com_port==7) port_name = L"\\\\.\\COM7";
	if(com_port==8) port_name = L"\\\\.\\COM8";

    char init[] = "";

    /////OPEN THE PORT
    file = CreateFile(port_name,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (INVALID_HANDLE_VALUE == file) {
        sys_err("ERR_INVALID_HANDLE_VALUE");
        return "1";
    }

    //configure the system
	//system error messages
    memset(&port, 0, sizeof(port));
    port.DCBlength = sizeof(port);
    if (!GetCommState(file, &port)) sys_err("ERR_GetCommState");
    if (!BuildCommDCB(L"baud=9600 parity=n data=8 stop=1", &port)) sys_err("ERR_BuildCommDCB");
    if (!SetCommState(file, &port)) sys_err("ERR_SetCommState");

    // Configure the timeouts
    timeouts.ReadIntervalTimeout = 3;
    timeouts.ReadTotalTimeoutMultiplier = 3;
    timeouts.ReadTotalTimeoutConstant = 2;
    timeouts.WriteTotalTimeoutMultiplier = 3;
    timeouts.WriteTotalTimeoutConstant = 2;
    if (!SetCommTimeouts(file, &timeouts)) sys_err("ERR_SetCommTImeouts");
    if (!EscapeCommFunction(file, CLRDTR)) sys_err("ERR_CLRDTR"); Sleep(200);
    if (!EscapeCommFunction(file, SETDTR)) sys_err("ERR_SETDTR");
    if (!WriteFile(file, init, sizeof(init), &written, NULL)) sys_err("ERR_WriteFile");
    if (written != sizeof(init)) sys_err("ERR_sizeof(init)");


	if(device !=3) {	
		WriteFile(file, &msg, (sizeof(msg)), &written, NULL);
		Sleep(50); 
		ReadFile(file, buffer, 50, &read, NULL);
		Sleep(50);
	}

	if(device==3) {
		for(int i=0;i<2;i++) {
			WriteFile(file, &msg, (sizeof(msg)), &written, NULL);
			Sleep(50); 
			ReadFile(file, buffer, 50, &read, NULL);
		}
	}

	Sleep(50);

    CloseHandle(file);

	string buff(buffer,50);

	if(buff.find("\r")==false) buff += "\r";
	
	return buff;
}