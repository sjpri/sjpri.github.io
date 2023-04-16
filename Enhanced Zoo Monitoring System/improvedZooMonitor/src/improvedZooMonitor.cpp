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
#include <cctype>
#include <stdlib.h>

int menu();
int adAnimal();
void displayAnimal ();
void displayHabitat ();


using namespace std;

//Main menu
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

	switch (userInput) {

	case 0:
		cout << "Shutting down Monitoring program" << endl;
		exit(0);
		break;

	case 1:
		cout << "Initializing Animals monitor" << endl;
		displayAnimal();
		break;

	case 2:
		cout << "Initializing Habitats monitor" << endl;
		displayHabitat();
		break;

	default:
		cout << "ERROR: Please make a valid selection" << endl;
		menu();
		break;
	}

	return 0;
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

//Add new animals to Animal's table
int adAnimal() {
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

	//Collect the variables to be inserted
	cout << "Enter the New animal: " << endl;
	cin >> newAnimal;
	//Convert string to upper case
	for (int i = 0; i < newAnimal.length(); i++) {
	        newAnimal[i] = toupper(newAnimal[i]);
	    }

	cout << "Enter the animal's name: " << endl;
	cin >> newName;
	//Convert string to upper case
	for (int i = 0; i < newName.length(); i++) {
	        newName[i] = toupper(newName[i]);
	    }

	cout << "Enter the animal's age: " << endl;
	cin >> newAge;

	cout << "Enter new health concerns: " << endl;
	cin >> newHealthConcerns;
	//Convert string to upper case
	for (int i = 0; i < newHealthConcerns.length(); i++) {
	        newHealthConcerns[i] = toupper(newHealthConcerns[i]);
	    }

	cout << "Enter new animal's feeding schedule: " << endl;
	cin >> newFeedingSchedule;
	//Convert string to upper case
	for (int i = 0; i < newFeedingSchedule.length(); i++) {
	        newFeedingSchedule[i] = toupper(newFeedingSchedule[i]);
	    }

	//open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Animal's table, sets new animal ID
	countSql = "SELECT COUNT(ID) FROM 'ANIMALS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);
	newID = count + 1;

	//Add rows to the Animals' table
	string sqlAddAnimals("INSERT INTO ANIMALS VALUES ('" + to_string(newID) + "', '" + newAnimal + "', '" + newName + "', '" + to_string(newAge) + "', '" + newHealthConcerns + "', '" + newFeedingSchedule + "');"
			);
	exit = sqlite3_exec(DB, sqlAddAnimals.c_str(), NULL, 0, &messaggeError);

	if (exit == SQLITE_OK) {
		std::cout << "Added " << newName << " successfully!" << std::endl;
		menu();
	}

	else {
		std::cerr << "Error adding new animal to the database" << std::endl;
		sqlite3_free(messaggeError);
	}

	return 0;
}

//Deletes existing animal from Animal's table
int deleAnimal() {
	//Set variables
	sqlite3* DB;
	int selectedID;
	int exit = 0;
	char* messaggeError;
	char *countSql;
	int count = 0;
	int rc;

	cout << "Initializing delete an animal" << endl;

	//Open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Animal's table, sets new animal ID
	countSql = "SELECT COUNT(ID) FROM 'ANIMALS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);

	//Show ID and Animals in list
	string animalsQuery = "SELECT ID, ANIMAL FROM 'ANIMALS';";
	sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);

	cout << "Please enter the Animal ID to be deleted: " << endl;
	cin >> selectedID;

	//If the user types a valid animal number, display the animal's information
	if (selectedID <= count) {
		//Delete animal
		cout << "Deleting selected animal" << endl;

		string delAnimal = "DELETE FROM ANIMALS WHERE ID = '" + to_string(selectedID) + "';";
		exit = sqlite3_exec(DB, delAnimal.c_str(), NULL, 0, &messaggeError);

		//Adjust remainder IDs
		while (selectedID <= count) {
			int nextID = selectedID + 1;
			string updateAnimal = "UPDATE ANIMALS SET ID = '" + to_string(selectedID) + "' WHERE ID = '" + to_string(nextID) + "';";
			exit = sqlite3_exec(DB, updateAnimal.c_str(), NULL, 0, &messaggeError);

			selectedID = selectedID + 1;
		}

		//Return to menu
		menu();

	}

	else {
		cout << "ERROR: Please enter a valid animal ID to be deleted" << endl;

		//Show ID and Animals in list
		string animalsQuery = "SELECT ID, ANIMAL FROM 'ANIMALS';";
		sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);
	}

	return 0;
}

//Animal's menu
void displayAnimal () {
	//Initiate variables
	sqlite3* DB;
	int userInput;
	int exit = 0;
	char *countSql;
	int count = 0;
	char* messaggeError;
	int rc;
	int addAnimal;
	int deleteAnimal;

	//Open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Animal's table
	countSql = "SELECT COUNT(ID) FROM 'ANIMALS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);

	//Show ID and animals from the Animals table and displays animals menu
	//Displays menu options
	cout << "0- Return to Main Menu" << endl;
	string animalsQuery = "SELECT ID, ANIMAL FROM 'ANIMALS';";
	sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);
	addAnimal = count + 1;
	deleteAnimal = count + 2;
	cout << addAnimal << "- Add new animal" << endl;
	cout << deleteAnimal << "- Delete an animal" << endl;
	cin >> userInput;

		//If the user types '0', go back to the main menu
		if (userInput == 0) {
			menu();
		}

		//If user inputs "Add new animal"
		else if (userInput == addAnimal) {
			adAnimal();
		}

		else if (userInput == deleteAnimal) {
			deleAnimal();
		}

		//If the user types a valid animal number, display the animal's information
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

//Add new habitat to Habitat's table
int adHabitat() {
	//Initiate variables
	sqlite3* DB;
	string userInput;
	int exit = 0;
	char *countSql;
	int count = 0;
	char* messaggeError;
	int rc;
	int newID;
	string newHabitat;
	string newTemperature;
	string newFoodSource;
	string newCleanliness;

	cout << "Initializing Add an animal" << endl;

	//Collect the variables to be inserted
	cout << "Enter the New habitat: " << endl;
	cin >> newHabitat;
	//Convert string to upper case
	for (int i = 0; i < newHabitat.length(); i++) {
	        newHabitat[i] = toupper(newHabitat[i]);
	    }

	cout << "Enter the habitat's temperature: " << endl;
	cin >> newTemperature;
	//Convert string to upper case
	for (int i = 0; i < newTemperature.length(); i++) {
		newTemperature[i] = toupper(newTemperature[i]);
	    }

	cout << "Enter new food source: " << endl;
	cin >> newFoodSource;
	//Convert string to upper case
	for (int i = 0; i < newFoodSource.length(); i++) {
		newFoodSource[i] = toupper(newFoodSource[i]);
	    }

	cout << "Enter new habitat's cleanliness: " << endl;
	cin >> newCleanliness;
	//Convert string to upper case
	for (int i = 0; i < newCleanliness.length(); i++) {
		newCleanliness[i] = toupper(newCleanliness[i]);
	    }

	//open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Habitat's table, sets new animal ID
	countSql = "SELECT COUNT(ID) FROM 'HABITATS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);
	newID = count + 1;

	//Add rows to the Habitat' table
	string sqlAddHabitats("INSERT INTO HABITATS VALUES ('" + to_string(newID) + "', '" + newHabitat + "', '" + newTemperature + "', '" + newFoodSource + "', '" + newCleanliness + "');"
			);
	exit = sqlite3_exec(DB, sqlAddHabitats.c_str(), NULL, 0, &messaggeError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error adding new habitat to the database" << std::endl;
		sqlite3_free(messaggeError);
	}

	else {
		std::cout << "Added " << newHabitat << " successfully!" << std::endl;
		menu();
	}

	//menu();

	return 0;
}

//Deletes an existing habitat from the habitat's table
int deleHabitat() {
	//Set variables
	sqlite3* DB;
	int selectedID;
	int exit = 0;
	char* messaggeError;
	char *countSql;
	int count = 0;
	int rc;

	cout << "Initializing delete a habitat" << endl;

	//Open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Habitat's table, sets new habitat ID
	countSql = "SELECT COUNT(ID) FROM 'HABITATS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);

	//Show ID and Habitats in list
	string habitatsQuery = "SELECT ID, HABITAT FROM 'HABITATS';";
	sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);

	cout << "Please enter the Habitat ID to be deleted: " << endl;
	cin >> selectedID;

	//If the user types a valid habitat number, display the animal's information
	if (selectedID <= count) {
		//Delete animal
		cout << "Deleting selected habitat" << endl;

		string delHabitat = "DELETE FROM HABITATS WHERE ID = '" + to_string(selectedID) + "';";
		exit = sqlite3_exec(DB, delHabitat.c_str(), NULL, 0, &messaggeError);

		//Adjust remainder IDs
		while (selectedID <= count) {
			int nextID = selectedID + 1;
			string updateHabitat = "UPDATE HABITATS SET ID = '" + to_string(selectedID) + "' WHERE ID = '" + to_string(nextID) + "';";
			exit = sqlite3_exec(DB, updateHabitat.c_str(), NULL, 0, &messaggeError);

			selectedID = selectedID + 1;
		}

		menu();
	}

	else {
		cout << "ERROR: Please enter a valid habitat ID to be deleted" << endl;

		//Show ID and Habitats in list
		string animalsQuery = "SELECT ID, HABITAT FROM 'HABITATS';";
		sqlite3_exec(DB, animalsQuery.c_str(), callback, 0, NULL);
	}

	return 0;
}

//Habitat's menu
void displayHabitat () {
	//Initiate variables
	sqlite3* DB;
	int userInput;
	int exit = 0;
	char *countSql;
	int count = 0;
	char* messaggeError;
	int rc;
	int addHabitat;
	int deleteHabitat;

	//Open database
	exit = sqlite3_open("AnimalDatabase.db", &DB);

	//Converts the SELECT COUNT to int, to count the number of IDs from the Habitat's table
	countSql = "SELECT COUNT(ID) FROM 'HABITATS';";
	rc = sqlite3_exec(DB, countSql, countCallback, &count, &messaggeError);

	//Show ID and habitat from the Habitat's table and displays habitat menu
	//Displays menu options
	cout << "0- Return to Main Menu" << endl;
	string habitatsQuery = "SELECT ID, HABITAT FROM 'HABITATS';";
	sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);
	addHabitat = count + 1;
	deleteHabitat = count + 2;
	cout << addHabitat << "- Add new habitat" << endl;
	cout << deleteHabitat << "- Delete an habitat" << endl;
	cin >> userInput;

		//If the user types '0', go back to the main menu
		if (userInput == 0) {
			menu();
		}

		//If user inputs "Add new habitat"
		else if (userInput == addHabitat) {
			adHabitat();
		}

		else if (userInput == deleteHabitat) {
			deleHabitat();
		}

		//If the user types a valid habitat number, display the habitat's information
		else if (userInput <= count) {
			//Command to show selected habitat from the Habitats table using the user input
			std::string selectedHabitat = "SELECT * FROM 'HABITATS' WHERE ID = '" + to_string(userInput) + "'";
			sqlite3_exec(DB, selectedHabitat.c_str(), callback, 0, NULL);

			cout << "PRESS 0 TO GO BACK TO THE ANIMALS MENU" << endl;
			cin >> userInput;

			if (userInput == 0) {
				//Loop back to the main Habitat options
				displayHabitat();
			}

			else {

				cout << "ERROR, PRESS 0 TO GO BACK TO HABITAT'S MENU" << endl;
			}

		}

		//If the user's input does not match an ID, display error and display the habitat choices again
		else {
			cout << "Error, please select a valid habitat" << endl;
			sqlite3_exec(DB, habitatsQuery.c_str(), callback, 0, NULL);
			cin >> userInput;
		}

	//close database
	sqlite3_close(DB);
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

	if (exit != SQLITE_CONSTRAINT || SQLITE_OK) {
		std::cerr << "Error with the database, code: "<< exit << std::endl;
		sqlite3_free(messaggeError);
	}

	else
		menu();

	//close database
	sqlite3_close(DB);
	return 0;
}


