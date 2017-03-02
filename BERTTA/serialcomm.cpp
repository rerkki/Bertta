#include "serialcomm.h"
#include "sqlite3.h"

void system_error(char *name) {

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

__declspec(dllexport) string read2()
{
	return("hello world!!!!");
}

__declspec(dllexport) string read(int com_port, int device, char *msg_)
{
    int ch;

	char buffer[50];

	for(int i=0;i<50;i++) buffer[i]=NULL;

	char msg[sizeof(msg_)];

	strcpy(msg, msg_);

    HANDLE file;
    COMMTIMEOUTS timeouts;
    DWORD read, written;
    DCB port;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;

	LPCWSTR port_name;
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
        system_error("missing file");
        return "1";
    }

    //configure the system
	//system error messages
    memset(&port, 0, sizeof(port));
    port.DCBlength = sizeof(port);
    if (!GetCommState(file, &port)) system_error("Could not open the port");
    if (!BuildCommDCB(L"baud=9600 parity=n data=8 stop=1", &port)) system_error("DCB blocked");
    if (!SetCommState(file, &port)) system_error("Incorrect port configuration");

    // Configure the timeouts
    timeouts.ReadIntervalTimeout = 3;
    timeouts.ReadTotalTimeoutMultiplier = 3;
    timeouts.ReadTotalTimeoutConstant = 2;
    timeouts.WriteTotalTimeoutMultiplier = 3;
    timeouts.WriteTotalTimeoutConstant = 2;
    if (!SetCommTimeouts(file, &timeouts)) system_error("Timeouts could not be configured");
    if (!EscapeCommFunction(file, CLRDTR)) system_error("DTR could not be closed"); Sleep(200);
    if (!EscapeCommFunction(file, SETDTR)) system_error("DTR could not be started");
    if (!WriteFile(file, init, sizeof(init), &written, NULL)) system_error("Data could not be written to the port");
    if (written != sizeof(init)) system_error("Some of the data could not be sent through the port");

	WriteFile(file, &msg, (sizeof(msg) - 1), &written, NULL); // Laudaa varten lyhyempi buffer

	Sleep(200);

	ReadFile(file, buffer, 50, &read, NULL);

	Sleep(100);

    CloseHandle(file);

	string buff(buffer,50);

	if(buff.find("\r")==false) buff += "\r";
	
	return buff;
}