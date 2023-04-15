//============================================================================
// Name        : improvedZooMonitor.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;


//invoke Callback to select data from database
static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*) data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}


int main(int argc, char** argv) {

	sqlite3* DB;

	//Create Animals table
	std::string sql = "CREATE TABLE ANIMALS("
					  "ANIMAL 	TEXT PRIMARY KEY 	NOT NULL, "
					  "NAME 	TEXT				NOT NULL, "
					  "AGE 	INT					NOT NULL, "
					  "HEALTH_CONCERNS 	TEXT		NOT NULL, "
					  "FEEDING_SCHEDULE 	TEXT		NOT NULL );";

	int exit = 0;
	char* messaggeError;
	exit = sqlite3_open("AnimalDatabase.db", &DB);
	string query = "SELECT * FROM ANIMALS;";

	string sqlAddAnimals(
			"INSERT INTO ANIMALS VALUES ('LION', 'LEO', 5, 'CUT ON LEFT FRONT PAW', 'TWICE DAILY');"
			"INSERT INTO ANIMALS VALUES ('TIGER', 'MAJ', 15, 'NONE', '3X DAILY');"
			"INSERT INTO ANIMALS VALUES ('BEAR', 'BALOO', 1, 'NONE', 'NONE ON RECORD');"
			"INSERT INTO ANIMALS VALUES ('GIRAFFE', 'SPOTS', 12, 'NONE', 'GRAZING');"
			);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);


	if (exit != SQLITE_OK) {
		std::cerr << "Error inserting into Animals Table" << std::endl;
		sqlite3_free(messaggeError);
	}

	else
		sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

		/*
		//Displays menu section
		cout << "WELCOME TO NATIONAL ZOO" << endl;
		cout << "" << endl;
		cout << "0- To exit the program" << endl;
		cout << "1- To monitor animals" << endl;
		cout << "2- To monitor habitats" << endl;
		*/

	sqlite3_close(DB);
	return 0;
}
