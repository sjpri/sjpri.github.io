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
	cout << "3- To edit animal's information" << endl;
	cout << "4 - To edit habitat's information" << endl;

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

//Invoke callback to count the number of rows in tables
extern "C" int countCallback(void* data, int count, char** rows,char**)
{
    if (count == 1 && rows) {
        *static_cast<int*>(data) = atoi(rows[0]);
        return 0;
    }
    return 1;
}

void displayAnimal () {
	//Initiate vqariables
	sqlite3* DB;
	int userInput;
	int exit = 0;
	char *countSql;
	int count = 0;
	char* messaggeError;
	int rc;

	//Open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Animal's table
	countSql = "SELECT COUNT(ID) FROM 'ANIMALS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);

	//Command to show ID and animals from the Animals table and displays animals menu
	string animalsQuery = "SELECT ID, ANIMAL FROM 'ANIMALS';";
	sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);

	//Displays menu options
	cout << "SELECT AN ANIMAL ID, " << endl;
	cout << "or select 0 to return to Main Menu" << endl;
	cin >> userInput;

		//If the user types '0', go back to the main menu
		if (userInput == 0) {
			menu();
		}

		//If the user typer a valid animal number, display the animal's information
		else if (userInput <= count) {
			//Command to show selected animal from the Animals table using the user input
			std::string selectedAnimal = "SELECT * FROM 'ANIMALS' WHERE ID = '" + to_string(userInput) + "'";
			sqlite3_exec(DB, selectedAnimal.c_str(), callback, 0, NULL);

			cout << "PRESS 0 TO GO BACK TO THE ANIMALS MENU" << endl;
			cin >> userInput;

			if (userInput == 0) {
				//Loop back to the main Animal options
				displayAnimal();
			}

			else {
				cout << "ERROR, PRESS 0 TO GO BACK TO ANIMALS MENU" << endl;
			}

		}

		//If the user's input does not match an ID, display error and display the animal choices again
		else {
			cout << "Error, please select a valid animal" << endl;
			sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);
			cin >> userInput;
		}

	//close database
	sqlite3_close(DB);

}

void displayHabitat () {
	//Initiate variables
	sqlite3* DB;
	int userInput;
	int exit = 0;
	char *countSql;
	int count = 0;
	char* messaggeError;
	int rc;

	//Open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Habitat's table
	countSql = "SELECT COUNT(ID) FROM 'HABITATS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);

	//Command to show ID and animals from the Habitats table and displays animals menu
	string habitatsQuery = "SELECT ID, HABITAT FROM 'HABITATS';";
	sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);

	//Displays menu options
	cout << "SELECT A HABITAT ID, " << endl;
	cout << "or select 0 to return to Main Menu" << endl;
	cin >> userInput;

	//Loop through the Habitats menu
	while (1) {

		//If the user types '0', go back to the main menu
		if (userInput == 0) {
			menu();
		}

		//If the user typer a valid habitat number, display the habitat's information
		else if (userInput <= count) {
			//Command to show selected animal from the Animals table using the user input
			std::string selectedHabitat = "SELECT * FROM 'HABITATS' WHERE ID = '" + to_string(userInput) + "'";
			sqlite3_exec(DB, selectedHabitat.c_str(), callback, 0, NULL);

			cout << "PRESS 0 TO GO BACK TO THE HABITATS MENU" << endl;
			cin >> userInput;

			if (userInput == 0) {
				//Loop back to the main Animal options
				displayHabitat();
			}

			else {
				cout << "ERROR, PRESS 0 TO GO BACK TO HABITATS MENU" << endl;
			}
		}

		//If the user's input does not match an ID, display error and display the animal choices again
		else {
			cout << "Error, please select a valid habitat" << endl;
			sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);
			cin >> userInput;
		}
	}

	//close database
	sqlite3_close(DB);

}

/*
int addAnimal(int argc, char** argv) {
	//Initiate variables
	sqlite3* DB;
	string userInput;
	int exit = 0;
	char *countSql;
	int count = 0;
	char* messaggeError;
	int rc;
	int newID;
	string newAnimal;
	string newName;
	int newAge;
	string newHealthConcerns;
	string newFeedingSchedule;

	cout << "Initializing Add an animal" << endl;

	//open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Animal's table, sets new animal ID
	countSql = "SELECT COUNT(ID) FROM 'ANIMALS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);
	newID = count++;

	return 0;
}

void deleteAnimal() {
	cout << "Initializing delete an animal" << endl;
}
*/

void editAnimalsMenu () {
	//Initiate variables
	int userInput;

	//Display menu options
	cout << "1- To add a new animal" << endl;
	cout << "2- To delete an existing animal" << endl;
	cout << "0- To go back to the Main Menu" << endl;
	cin >> userInput;

	switch(userInput) {
	case 0:
		menu();
		break;

	case 1:
		//addAnimal();
		break;

	case 2:
		//deleteAnimal();
		break;
	}

}

void editHabitatsMenu () {
	//Initiate variables
	int userInput;

	//Display menu options
	cout << "1- To add a new habitat" << endl;
	cout << "2- To delete an existing habitat" << endl;
	cin >> userInput;

}

int main(int argc, char** argv) {
	//Initiate variables
	int exit = 0;
	sqlite3* DB;
	char* messaggeError;
	int userInput;
	string habitatsQuery = "SELECT HABITAT FROM 'HABITATS';";

	//Open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);


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

	while (1) {

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
			displayHabitat();
			break;

		case 3:
			cout << "Initializing edit animals" << endl;
			editAnimalsMenu();
			break;

		case 4:
			cout << "Initializing edit habitats" << endl;
			editHabitatsMenu();
			break;

		default:
			cout << "ERROR: Please make a valid selection" << endl;
			menu();
			break;
		}

	}

	//close database
	sqlite3_close(DB);
	return 0;
}


