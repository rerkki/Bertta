#include <stdio.h>
#include <conio.h>
#include <iomanip>
//#include <algorithm>
#include "sqlite3.h"
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

// SQLITE Callback
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	
	for(i=0; i<argc; i++){

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	}

	printf("\n");
	
	return 0;
}

__declspec(dllexport) int create_db(void)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\test12.db", &db);
 //  rc = sqlite3_open("test12.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(rc);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE BERTTA(ID INTEGER PRIMARY KEY AUTOINCREMENT, HEIDOLPH, LAUDA, METTLER1, METTLER2);";

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


__declspec(dllexport) int insert_db(int heidolph, double lauda, double mettler1, double mettler2)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\test12.db", &db);
//   rc = sqlite3_open("test12.db", &db);
   if( rc ){
    //  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   }else{
    //  fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */

   sql = sqlite3_mprintf("INSERT INTO BERTTA (HEIDOLPH, LAUDA, METTLER1, METTLER2) VALUES ('%d','%.2f','%.2f','%.2f');", heidolph, lauda, mettler1, mettler2);
   cout<<sql<<endl;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
//      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
//      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);

   return rc;
 
}

int rows()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	int count = 0;

	/* Open database */
	rc = sqlite3_open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\test12.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	//   sql = "SELECT METTLER from BERTTA";
	sql = "SELECT count(*) FROM BERTTA";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, &count, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);

	printf("count: %d\n", count);

	return count;
}



int select_db()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\test12.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
//   sql = "SELECT METTLER from BERTTA";
   sql = "SELECT Count(*) FROM BERTTA";

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


// Function that prints selected columns to console and to file

__declspec(dllexport) void TableSave(int exec)
{
	if (exec == 1) getTableData();
}


__declspec(dllexport) int getTableData()
{
	ofstream myfile;
	myfile.open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\example.csv");

   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\test12.db", &db);
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

					myfile << s << ";";
					
                }
                cout << endl;
				myfile << "\n";
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
				myfile.close();
				sqlite3_close(db);
                break;
            }    
        }
    }
	return 0;
}


__declspec(dllexport) int getColData(int nrows, int col1, int col2, int col3, int col4)
{
	string col1_, col2_, col3_, col4_;

	int rcount = 0;

	if (col1 == 0) col1_ = "ID";
	if (col1 == 1) col1_ = "HEIDOLPH";
	if (col1 == 2) col1_ = "LAUDA";
	if (col1 == 3) col1_ = "METTLER1";
	if (col1 == 4) col1_ = "METTLER2";


	if (col2 == 0) col2_ = "";
	if (col2 == 2) col2_ = ", LAUDA";
	if (col2 == 3) col2_ = ", METTLER1";
	if (col2 == 4) col2_ = ", METTLER2";

	if (col3 == 0) col3_ = "";
	if (col3 == 3) col3_ = ", METTLER1";
	if (col3 == 4) col3_ = ", METTLER2";

	if (col4 == 0) col4_ = "";
	if (col4 == 4) col4_ = ", METTLER2";


	ofstream myfile;
	myfile.open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\example.csv");

	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char sql[60] = { 0 };
	string sql_ = "SELECT " + col1_ + col2_ + col3_ + col4_ + " FROM BERTTA";

	cout << sql_ << endl;
	getch();

	/* Open database */
	rc = sqlite3_open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\test12.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		fprintf(stdout, "Opened database successfully\n");
	}

	sqlite3_stmt *statement;
	getch();
	//sql = "SELECT HEIDOLPH, LAUDA, METTLER1, METTLER2 FROM BERTTA";
	strcpy(sql, sql_.c_str());

	if (sqlite3_prepare(db, sql, -1, &statement, 0) == SQLITE_OK)
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while (1)
		{
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW)
			{
				for (int i = 0; i < ctotal; i++)
				{
					string s = (char*)sqlite3_column_text(statement, i);

					// print or format the output as you want 
					cout << s << " ";

					myfile << s << ";";

					rcount += 1;
				}
				cout << endl;
				myfile << "\n";
			}

			if (res == SQLITE_DONE || res == SQLITE_ERROR || rcount == nrows)
			{
				cout << "done " << endl;
				myfile.close();
				sqlite3_close(db);
				break;
			}
		}
	}
	return 0;
}

__declspec(dllexport) void getColToArr(int nrows, int col, double * values)
{
	string col1;

	if (nrows < 2) nrows = 2;

	int rcount = 0;

	if (col == 1) col1 = "HEIDOLPH";
	if (col == 2) col1 = "LAUDA";
	if (col == 3) col1 = "METTLER1";
	if (col == 4) col1 = "METTLER2";

	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char sql[60] = { 0 };
	string sql_ = "SELECT " + col1 + " FROM BERTTA ORDER BY METTLER2 DESC";

//	cout << sql_ << endl;
//	getch();

	/* Open database */
	rc = sqlite3_open("C:\\Users\\xlaraser\\Desktop\\SQLITE3\\test12.db", &db);
//	if (rc) {
//		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		//return(0);
//	}
//	else {
//		fprintf(stdout, "Opened database successfully\n");
//	}

	sqlite3_stmt *statement;
	getch();
	//sql = "SELECT HEIDOLPH, LAUDA, METTLER1, METTLER2 FROM BERTTA";
	strcpy(sql, sql_.c_str());

	if (sqlite3_prepare(db, sql, -1, &statement, 0) == SQLITE_OK)
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while (1)
		{
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW)
			{
				for (int i = 0; i < ctotal; i++)
				{
					double s = atof((char*)sqlite3_column_text(statement, i));

					// print or format the output as you want 
					//cout << s << " ";

					//myfile << s << ";";

					values[rcount] = s;

					rcount += 1;
				}
				//cout << endl;
			}

			if (res == SQLITE_DONE || res == SQLITE_ERROR || rcount == nrows - 1)
			{
				//cout << "done " << endl;
				sqlite3_close(db);
				break;
			}
		}
	}
}



// Function to call Mettler balance, returns weight in grams
__declspec(dllexport) double mettler(int port, int msg) {

	char * msg_;
	char mettler_str[50] = { 0 };
	string val;
	int msglen;

	if (msg == 1) msg_ = "S\r\n";

	strcpy(mettler_str, read(port,1,msg_).c_str());
	Sleep(60);
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

	char rpm_[16] = { 0 };
	rpm(speed, rpm_);
	read(port, 2, rpm_);
	Sleep(60);
//	strcpy(output, read(port, 2, rpm_).c_str());
}



__declspec(dllexport) void lauda(int port, double set_temp) {

	char temp_[18] = { 0 };
	temp(set_temp, temp_);
	cout << temp_ << endl;
	read(port,3,temp_);
}

__declspec(dllexport) double pt100(double temp) {

	return temp;
}



int main() {

//	long unsigned int now = millisec();

//	lauda(1, 33.2);

	create_db();

	cout << insert_db(1, 2, 3, 4) << endl;

//	getTableData();

	
	getColData(10,0,0,0,0);

//	string valueArr[5000];
//	getColToArr(5000, 4, valueArr);

//	for (int i = 0; i < 5000; i++) cout << valueArr[i] << endl;
	
//	select_db();
//	cout << "xxx" << rows() << endl;
//	TableSave(1);
/*	long unsigned int time_params[2] = { 0 };

	elapsed(now, time_params);

	cout << now << endl;
	cout << time_params[0] << endl;
	cout << time_params[1] << endl;
	*/
	getch();
}


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