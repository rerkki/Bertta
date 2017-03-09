#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <algorithm>
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


int insert_db(double mettler, char * heidolph, char * lauda)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test10.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */

   sql = sqlite3_mprintf("INSERT INTO BERTTA (METTLER, HEIDOLPH, LAUDA) VALUES ('%.2f', '%q','%q'); ", mettler, heidolph, lauda);
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




double parsedbl(char * msg) {

	int msglen = strlen(msg);

	string val;

	for(int i=0;i<msglen;i++) {

		if(isdigit(msg[i])) val += msg[i];
		if(msg[i]=='.') val += msg[i];
		if(msg[i]=='+') val += msg[i];
		if(msg[i]=='-') val += msg[i];

	}
	return atof(val.c_str());
}


///// LOOP that communicates with serial devices and writes communication to database
int mainloop(	int dev1, int dev2, int dev3,
				int port1, int port2, int port3,
				char * msg1, char * msg2, char *msg3){


	char mettler_str[50]; 
	char heidolph[50];
	char lauda[50];
	double mettler;

	for(int i=0; i<50; i++){
		mettler_str[i]=0;
		heidolph[i]=0;
		lauda[i]=0;
	}

	if(dev1 > 0){ 
		strcpy(mettler_str, read(port1,dev1,msg1).c_str());
	}else{
		mettler_str[0]='0';
	}

	if(dev2 > 0){
		strcpy(heidolph, read(port2,dev2,msg2).c_str());
	}else{
		heidolph[0]='X';
	}

	if(dev3 > 0){
		strcpy(lauda, read(port3,dev3,msg3).c_str());
	}else{
		lauda[0]='X';
	}

	mettler = parsedbl(mettler_str);

//	cout<<mettler<<endl;
//	cout<<lauda<<endl;
//	cout<<heidolph<<endl;

	create_db();
	insert_db(mettler, heidolph, lauda);
	//select_db();
	//strip_db();
	getTableData();

getch();

return 0;
}


__declspec(dllexport) int testfunc(int a) {

	return a;
}

int main() {

	mainloop(1,0,0,5,8,8,"S\r\n","R120\r\n","OUT_SP_00_022.1\r\n");


	return 0;

}

