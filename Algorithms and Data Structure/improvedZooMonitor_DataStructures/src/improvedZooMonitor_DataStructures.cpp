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

int menu() {
	int userInput;

	//Displays menu section
	cout << "WELCOME TO NATIONAL ZOO" << endl;
	cout << "" << endl;
	cout << "0- To exit the program" << endl;
	cout << "1- To monitor animals" << endl;
	cout << "2- To monitor habitats" << endl;

	cout << "Please enter your selection: " << endl;
	cin >> userInput;

	return userInput;
}

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

/*
static int countCallback(void* count, int argc, char** argv, char** azColName) {
    int c = count;
    c = atoi(argv[0]);
    return 0;
}
*/

void displayAnimal () {
	sqlite3* DB;
	int userInput;
	int exit = 0;

	exit = sqlite3_open("AnimalDatabase.db", &DB);
	string animalsQuery = "SELECT ID, ANIMAL FROM 'ANIMALS';";
	int count = 4;
	//string animalInput = "SELECT userInput FROM 'ANIMALS';";
	//string count = "SELECT COUNT(*) FROM 'ANIMALS';";
	//string count = "SELECT CAST(COUNT(ColumnA) AS REAL) AS Count FROM 'ANIMALS';";

	//Displays animals menu
	sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);
	//cout << "number of IDs: " << count << endl;
	//sqlite3_exec(DB, count.c_str(), callback, 0, NULL);
	cout << "Select an animal ID, or select 0 to return to Main Menu" << endl;
	cin >> userInput;

	if (userInput == 0) {
		menu();
	}

	else if (userInput <= count) {
		cout << "Display information from animal selected" << endl;
		displayAnimal();
	}

	else {
		cout << "Error, please select a valid animal" << endl;
		sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);
		cin >> userInput;
	}

	sqlite3_close(DB);

}

void displayHabitat () {
	sqlite3* DB;
	int userInput;
	int exit = 0;

	exit = sqlite3_open("AnimalDatabase.db", &DB);
	string habitatsQuery = "SELECT ID, HABITAT FROM 'HABITATS';";
	int count = 4;
	//string animalInput = "SELECT userInput FROM 'ANIMALS';";
	//string count = "SELECT COUNT(*) FROM 'ANIMALS';";
	//string count = "SELECT CAST(COUNT(ColumnA) AS REAL) AS Count FROM 'ANIMALS';";

	//Displays animals menu
	sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);
	//cout << "number of IDs: " << count << endl;
	//sqlite3_exec(DB, count.c_str(), callback, 0, NULL);
	cout << "Select a habitat ID, or select 0 to return to Main Menu" << endl;
	cin >> userInput;

	if (userInput == 0) {
		menu();
	}

	else if (userInput <= count) {
		cout << "Display information from habitat selected" << endl;
		displayHabitat();
	}

	else {
		cout << "Error, please select a valid habitat" << endl;
		sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);
		cin >> userInput;
	}

	sqlite3_close(DB);

}

int main(int argc, char** argv) {

	int exit = 0;
	sqlite3* DB;
	char* messaggeError;
	exit = sqlite3_open("AnimalDatabase.db", &DB);
	string habitatsQuery = "SELECT HABITAT FROM 'HABITATS';";


	//Create Animals table
	std::string sql = "CREATE TABLE ANIMALS("
					  "ID 	INT PRIMARY KEY 	NOT NULL, "
					  "ANIMAL 	TEXT 		 	NOT NULL, "
					  "NAME 	TEXT				NOT NULL, "
					  "AGE 	INT					NOT NULL, "
					  "HEALTH_CONCERNS 	TEXT		NOT NULL, "
					  "FEEDING_SCHEDULE 	TEXT		NOT NULL );";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

	//Create Habitat table
	std::string sqlHabitat = "CREATE TABLE HABITATS("
							 "ID 	INT PRIMARY KEY 	NOT NULL, "
							 "HABITAT 	TEXT 		 	NOT NULL, "
							 "TEMPERATURE 	TEXT 			NOT NULL, "
							 "FOOD_SOURCE 	TEXT			NOT NULL, "
							 "CLEANLINESS 	TEXT 			NOT NULL );";

	exit = sqlite3_exec(DB, sqlHabitat.c_str(), NULL, 0, &messaggeError);

	//Add rows to the Animals' table
	string sqlAddAnimals("INSERT INTO ANIMALS VALUES (1, 'LION', 'LEO', 5, 'CUT ON THE LEFT FRONT PAW', 'TWICE DAILY');"
						 "INSERT INTO ANIMALS VALUES (2, 'TIGER', 'MAJ', 15, 'NONE', '3X DAILY');"
						 "INSERT INTO ANIMALS VALUES (3, 'BEAR', 'BALOO', 1, 'NONE', 'NONE ON RECORD');"
						 "INSERT INTO ANIMALS VALUES (4, 'GIRAFFE', 'SPOTS', 12, 'NONE', 'GRAZING');"
			);
	exit = sqlite3_exec(DB, sqlAddAnimals.c_str(), NULL, 0, &messaggeError);

	//Add rows to the Habitats' table
	string sqlAddHabitats("INSERT INTO HABITATS VALUES (1, 'PENGUIN', 'FREEZING', 'FISH IN WATER RUNNING LOW', 'PASSED');"
						  "INSERT INTO HABITATS VALUES (2, 'BIRD', 'MODERATE', 'NATURAL FROM ENVIRONMENT', 'PASSED');"
						  "INSERT INTO HABITATS VALUES (3,  'AQUARIUM', 'VARIES WITH OUTPUT TEMPERATURE', 'ADDED DAILY', 'NEEDS CLEANING FROM ALGAE');"
			);
	exit = sqlite3_exec(DB, sqlAddHabitats.c_str(), NULL, 0, &messaggeError);

	//sqlAddAnimals = "DELETE FROM ANIMALS WHERE ANIMAL = 'TIGER';";

	if (exit != SQLITE_CONSTRAINT || SQLITE_OK) {
		std::cerr << "Error with the database, code: "<< exit << std::endl;
		sqlite3_free(messaggeError);
	}

	while(1) {
		switch (menu()) {
		case 0:
			cout << "Shutting down Monitoring program" << endl;
			break;

		case 1:
			cout << "Initializing Animals monitor" << endl;
			displayAnimal();
			break;

		case 2:
			cout << "Initializing Habitats monitor" << endl;
			//sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);
			displayHabitat();
			break;

		default:
			cout << "ERROR: Please make a valid selection" << endl;
			menu();
		}
	}

	sqlite3_close(DB);
	return 0;
}


