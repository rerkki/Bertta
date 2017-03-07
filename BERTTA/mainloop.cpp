#include <stdio.h>
#include <conio.h>
#include "sqlite3.h"
#include "serialcomm.h"
#include "mainloop.h"
#include <windows.h>




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
   rc = sqlite3_open("test9.db", &db);
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


int insert_db(char * mettler, char * heidolph, char * lauda)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test9.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */

   sql = sqlite3_mprintf("INSERT INTO BERTTA (METTLER, HEIDOLPH, LAUDA) VALUES ('%q','%q','%q'); ", mettler, heidolph, lauda);
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
   return 0;
}


int select_db()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("test9.db", &db);
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




///// LOOP that communicates with serial devices and writes communication to database
int mainloop(	int port1, int port2, int port3,
				int dev1, int dev2, int dev3,
				char * msg1, char * msg2, char *msg3){


	char mettler[50]; 
	char heidolph[50];
	char lauda[50];
	

	//Mettler
	port1 = 6;
	dev1 = 2;
	msg1 = "S\r\n"; //vaaka

	//Lauda
	port3 = 5;
	dev3 = 3;
	msg3 = "OUT_SP_00_033.3\r\n"; //Lauda

	//Heidolph
	port2 = 8;
	dev2 = 2;
	msg2 = "\r\n\R230\r\n"; // Heidolph

//	cout<<read(port2,dev2,msg2)<<endl;
//	cout<<read(port3,dev3,msg3)<<endl;
	

	strcpy(mettler, read(port1,dev1,msg1).c_str());

	strcpy(lauda, read(port3,dev3,msg3).c_str());

	strcpy(heidolph, read(port2,dev2,msg2).c_str());

//	cout<<lauda<<endl;
//	cout<<heidolph<<endl;
//	cout<<mettler<<endl;

	create_db();
	insert_db(mettler, heidolph, lauda);
	select_db();



getch();

return 0;
}


__declspec(dllexport) int testfunc(int a) {

	return a;
}

int main() {

	mainloop(6,5,8,1,3,2,"S\r\n","OUT_SP_00_032.1\r\n","R120\r\n");

	return 0;

}

