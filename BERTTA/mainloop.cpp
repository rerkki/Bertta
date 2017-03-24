#include <stdio.h>
#include <conio.h>
#include <iomanip>
//#include <algorithm>
#include "sqlite3.h"
#include "serialcomm.h"
#include "mainloop.h"
#include <windows.h>


double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, 1);




static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	
	for(i=0; i<argc; i++){

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	}

	printf("\n");
	
	return 0;
}

int create_db()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test10.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE BERTTA(METTLER, HEIDOLPH, LAUDA); ";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}


__declspec(dllexport) void insert_db(double mettler, int heidolph, int lauda)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   cout<<heidolph<<endl;

   /* Open database */
   rc = sqlite3_open("test10.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */

   sql = sqlite3_mprintf("INSERT INTO BERTTA (METTLER, HEIDOLPH, LAUDA) VALUES ('%.2f','%d','%d'); ", mettler, heidolph, lauda);
   //cout<<sql<<endl;


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
 
}


int select_db()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("test10.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * from BERTTA";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);

   return 0;
}


int strip_db()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("test10.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "UPDATE BERTTA SET METTLER = replace( METTLER, '\n', ' ');";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);

   return 0;
}


int getTableData()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test10.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }
	
	sqlite3_stmt *statement;    

    sql = "SELECT * from BERTTA";

    if ( sqlite3_prepare(db, sql, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
                for ( int i = 0; i < ctotal; i++ ) 
                {
                    string s = (char*)sqlite3_column_text(statement, i);

                    // print or format the output as you want 
					cout << s << " ";
                }
                cout << endl;
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }
	return 0;
}




string parseMsg(char * msg) {

	int msglen = strlen(msg);

	string val;

	for(int i=0;i<msglen;i++) {

		if(isdigit(msg[i])) val += msg[i];
		if(msg[i]=='.') val += msg[i];
		if(msg[i]=='+') val += msg[i];
		if(msg[i]=='-') val += msg[i];

	}
	return val.c_str();
}

__declspec(dllexport) double mettler(int port, int msg) {

	char * msg_;

	if (msg == 1) msg_ = "S\r\n";
	
	char mettler_str[50] = { 0 };
	string val;
	int msglen;

	//for(int i=0;i<50;i++) mettler_str[i]=0;

	strcpy(mettler_str, read(port,1,msg_).c_str());
	msglen = strlen(mettler_str);

	int v = 0;

	//cout << mettler_str << endl;

	//cout << read(port,1,msg_) << endl;

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
//		cout << val << endl;
	}
	val[v] = '\0';
	
	return atof(val.c_str());
	
}


__declspec(dllexport) void heidolph(int port, int speed, char * output) {

	char rpm_[16] = { 0 };

	rpm(speed, rpm_);

	read(port, 2, rpm_);

	Sleep(60);

	strcpy(output, read(port, 2, rpm_).c_str());
}



__declspec(dllexport) void lauda(int port, double set_temp) {

	char temp_[18] = { 0 };

	temp(set_temp, temp_);

	cout << temp_ << endl;

			read(port,3,temp_);
}

/*

int main() {

	char out[50] = { 0 };

	double w;

	heidolph(4, 50, out);
	w = mettler(5, 1);

	cout << out << "   "  << w <<endl;

//	lauda(4, 33.1);

//	cout << read(4, 3, "OUT_SP_00_033.0\r\n") << endl;

	getch();
}

*/
///// LOOP that communicates with serial devices and writes communication to database
/*
int main() {


for(int a=0;a<2;a++) {

	Sleep(300);
//	cout<<mettler(4,"S\r\n")<<endl;
//	cout<<heidolph(4,"R125\r\n")<<endl;
//	cout<<lauda(8,"OUT_SP_00_025.7\r\n")<<endl;
	cout << read(4, 1, "S\r\n") << endl;
	cout<<a<<endl;

	char newRpm[16]={0};
	char newTemp[17]={0};

	rpm((100+a), newRpm);

	temp((15 + 5), newTemp);

	cout<<newTemp<<endl;
	cout<<strlen(newTemp)<<endl;

	Sleep(200);

	char * mettler_comm = "S\r\n";
	char * heidolph_comm;
	char * lauda_comm = "OUT_SP_00_035.0\r\n"; // ALWAYS check the msg length

	Sleep(300);
	double mettler_ = mettler(4, mettler_comm);
	Sleep(300);
//	int heidolph_ = heidolph(4, newRpm);
	Sleep(300);
//	int lauda_ = lauda(5, newTemp);

	cout<<mettler_<<endl;

//	create_db();
//	insert_db(mettler_, heidolph_, lauda_);
//	getTableData();


	myPID.Compute();

//	getch();


}
	return 2;

}

*/