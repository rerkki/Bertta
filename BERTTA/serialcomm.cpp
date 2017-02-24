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


__declspec(dllexport) string read(string com_port, string msg_)
{
    int ch;
	string val;
 //  char buffer[1];
	char buffer[100];
	for(int i=0;i<100;i++) buffer[i]=0;

//	char msg = "S\r\n"; 
	const char * msg = msg_.c_str();

    HANDLE file;
    COMMTIMEOUTS timeouts;
    DWORD read, written;
    DCB port;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;

	LPCWSTR port_name;
	if(com_port=="3") port_name = L"\\\\.\\COM3";
	if(com_port=="4") port_name = L"\\\\.\\COM4";
	if(com_port=="5") port_name = L"\\\\.\\COM5";
	if(com_port=="6") port_name = L"\\\\.\\COM6";
	if(com_port=="7") port_name = L"\\\\.\\COM7";
	if(com_port=="8") port_name = L"\\\\.\\COM8";

    char init[] = "";


    // open the port
	
	
    file = CreateFile(port_name,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

	

/*

    if (INVALID_HANDLE_VALUE == file) {
        system_error("missing file");
        return 1;
    }
*/
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

    //Duty cycle
    do {
	//	WriteFile(file, "", 0, &written, NULL);
		WriteFile(file, &msg, (sizeof(msg) - 1), &written, NULL); // Laudaa varten lyhyempi buffer

		Sleep(200);

		ReadFile(file, buffer, 20, &read, NULL); //vaaka

		Sleep(10);
		
		//ch = 127;
		if (read) { 

			string buff(buffer, 100);
			cout<<buff<<endl;
			ch=127;
				/*
				if(isdigit(buffer[0])) val += buff; //cout<<buffer;
				if(buff==".") val += buff;
				if(buff=="O") val += buff;
				if(buff=="K") {val += buff; ch = 127;}
				if(buff=="E") val += buff;
				if(buff=="R") val += buff;
				if(buff=="_") {val += buff; ch=127;}
				if(buff=="g") ch = 127;
				*/

		} 
    } while(ch != 127);    // ch 127 is ctrl-backspace.

	Sleep(100);

    CloseHandle(file);
	
	return val;
}


int main() {

//	char const msg[] = "R100\r"; // Heidolph
//	char const msg[] = "S\r\n"; //vaaka
//	char const msg[] = "OUT_SP_00_23.33\r"; //Lauda

	for(int i=0;i<10;i++) {
		cout<<read("6", "S\r\n")<<endl;
	}

	getch();
}
