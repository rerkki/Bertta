#include <stdio.h>
#include <conio.h>
#include "sqlite3.h"
#include "serialcomm.h"
#include <windows.h>




static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	
	for(i=0; i<argc; i++){

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	}

	printf("\n");
	
	return 0;
}

//__declspec(dllexport) void db_create(char *db_name, char *tb_name){

void db_create(char *db_name, char *tb_name){


	sqlite3 *db;
	char *zErrMsg;
	int rc, ret;

	rc = sqlite3_open(db_name, &db);
	
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	}

	char* z = tb_name; 
	
	char* create_table1 = sqlite3_mprintf("create table %q(value)", z); 

	ret = sqlite3_exec(db, create_table1, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	char* create_table2 = sqlite3_mprintf("create table timestamp(time)");

	ret = sqlite3_exec(db, create_table2, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

}

__declspec(dllexport) void db_write(char *db_name, char *tb_name, char *date_time, double value){


	sqlite3 *db;
	char *zErrMsg;
	int rc, ret;

	rc = sqlite3_open(db_name, &db);
	
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	}

	char* z = tb_name; 
	
	char* write_db = sqlite3_mprintf("insert into %q values('%12.9f')", z, value); 

	ret = sqlite3_exec(db, write_db, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	char* write_db_time = sqlite3_mprintf("insert into timestamp values('%q')", date_time);

	ret = sqlite3_exec(db, write_db_time, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

} 

__declspec(dllexport) void db_write_value(char* date_time, double value){

	char* db_name = "test3.db";

	char* tb_name = "measurement";

	db_write(db_name,tb_name,date_time,value);

}


//__declspec(dllexport) void db_read(char *db_name, char *tb_name, double *results){
__declspec(dllexport) void db_read(char *db_name, char *tb_name, char *results){


	sqlite3 *db;
	char *zErrMsg;
	char **result;
	int rc, ret, rows, cols, length = 0;

	rc = sqlite3_open(db_name, &db);
	
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	}

	char* z = tb_name; 
	
	char* read_db = sqlite3_mprintf("select * from %q", z); 

	ret = sqlite3_get_table(db, read_db, &result, &rows, &cols, &zErrMsg);

	//length = cols * (rows+1);
	length = rows+1;

	printf("%i", length);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free_table(result);
	}
		
		for (int i=length-1; i<length; i++) {
		
			results[0] = atof(result[i]);
//			results[0] = result[i];

		}
	
	sqlite3_close(db);

} 

__declspec(dllexport) void db_read_values(int size_vec, double *values){

	char* db_name = "test3.db";

	char* tb_name = "measurement";

//	db_read(db_name,tb_name,values);

}


__declspec(dllexport) int db_length(char *db_name, char *tb_name){


	sqlite3 *db;
	char *zErrMsg;
	char **result;
	int rc, ret, rows, cols, length = 0;

	rc = sqlite3_open(db_name, &db);
	
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	}

	char* z = tb_name; 
	
	char* read_db = sqlite3_mprintf("select * from %q", z); 

	ret = sqlite3_get_table(db, read_db, &result, &rows, &cols, &zErrMsg);

	length = cols * (rows+1);

	sqlite3_close(db);

	return length;

} 

__declspec(dllexport) void db_readtext(char *db_name, char *tb_name){


	sqlite3 *db;
	char *zErrMsg;
	char **result;
	int rc, ret, rows, cols, length = 0;

	rc = sqlite3_open(db_name, &db);
	
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	}

	char* z = tb_name; 
	
	char* read_db = sqlite3_mprintf("select * from %q", z); 

	ret = sqlite3_exec(db, read_db, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

} 


//////BERTTA



__declspec(dllexport) void db_write_str(char *db_name, char *tb_name, char *value){


	sqlite3 *db;
	char *zErrMsg;
	int rc, ret;

	rc = sqlite3_open(db_name, &db);
	
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	}

	char* z = tb_name; 

	char* write_db_time = sqlite3_mprintf("insert into %q values('%q')", z, value);

	ret = sqlite3_exec(db, write_db_time, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

} 



int main() {

	int port;
	int dev;
	char * msg;
	

	//Mettler
	port = 6;
	dev = 1;
	msg = "S\r\n"; //vaaka

	//Heidolph
	//dev = 2;
	//msg = "R100\r"; // Heidolph

	//Lauda
	//dev = 3;
	//msg = "OUT_SP_00_23.33\r"; //Lauda

	for(int i=0;i<2;i++) {

	//	cout<<read(port,dev,msg)<<endl;
		cout<<read2()<<endl;

	}

	getch();
}


/*

int main()
{

//	double results[1];

//	for (int i=0;i<1;i++) results[i] = 0;

	char * date_time = "2017-03-01";

	char * str_val = "S\r\n";

//	for(int i=0;i<40;i++) results[i] = 0;

	db_create("test4.db","datetime");

	db_create("test4.db","param");

//	db_write("test3.db","measurement",9.784582957486);

//	db_write_value(date_time, atof(read2().c_str()));

	db_write_str("test4.db","datetime","param");

	db_read("test4.db","measurement",results);

	db_read_values(10, results);

//	db_readtext("test3.db","measurement");

//	db_readtext("test3.db","timestamp");


	for(int i=0;i<1;i++){

		printf("%-13.9f \n", results[i]);
	
	}
	cout<<read2()<<endl;

getch();

return 0;
}

*/

