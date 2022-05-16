#include <sqlite3.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int createDB(const char* s);
int createTable(const char* s);
//static int deleteData(const char* s);
int insertData(const char* s);
int updateData(const char* s);
int selectData(const char* s);
int callback(void* NotUsed, int argc, char** argv, char** azColName);

int main()
{
	const char* dir = R"(E:\FortyTwoLab\Student Database\STUDENTS.db)";

	createDB(dir);
	createTable(dir);
	deleteData(dir); 
	insertData(dir); 
	updateData(dir);
	selectData(dir);

	return 0;
}

int createDB(const char* s)
{
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(s, &DB);

	sqlite3_close(DB);

	return 0;
}

int createTable(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "CREATE TABLE IF NOT EXISTS GRADES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME      TEXT NOT NULL, "
		"GRADE     CHAR(1) );";

	try
	{
		int exit = 0;
		exit = sqlite3_open(s, &DB);
		
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error in createTable function." << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Table created Successfully" << endl;
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}

	return 0;
}

int insertData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql("INSERT INTO GRADES (NAME, GRADE) VALUES('Pratik','A');"
		"INSERT INTO GRADES (NAME, GRADE) VALUES('Vikas', 'B');"
		"INSERT INTO GRADES (NAME, GRADE) VALUES('Pradeep', 'C');");

	int exit = sqlite3_open(s, &DB);
	
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records inserted Successfully!" << endl;

	return 0;
}

int updateData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql("UPDATE GRADES SET GRADE = 'A' WHERE NAME = 'Alice'");

	int exit = sqlite3_open(s, &DB);
	
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in updateData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records updated Successfully!" << endl;

	return 0;
}

int deleteData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "DELETE FROM GRADES;";

	int exit = sqlite3_open(s, &DB);
	
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error in deleteData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records deleted Successfully!" << endl;

	return 0;
}

int selectData(const char* s)
{
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM GRADES;";

	int exit = sqlite3_open(s, &DB);
	
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records selected Successfully!" << endl;

	return 0;
}


int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	cout << endl;

	return 0;
}



