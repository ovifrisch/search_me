#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "Database.h"

int main(int argc, char* argv[]) {
	string user_line;

	ofstream my_file;

	if (argc > 1 && strcmp(argv[1], "clean") == 0)
		my_file.open("database.txt", ios::out);
	else
		my_file.open("database.txt", ios::app);

	Database* db = new Database();

	while(true) {
		getline(cin, user_line);
		if (user_line.compare("help") == 0)
			cout << "Enter e to exit, otherwise enter some data and hit enter." << endl;

		else if (user_line.compare("e") == 0)
			break;

		else {
			my_file << user_line << '\n';
			db->add_node(user_line);
		}
	}

	my_file.close();


}

/*
	you write some shit, store it locally on the heap,
	then when the user exits store it (or append) to a
	file on disk. The point of having this database,
	remember, is to extract information from it upon
	a request. so when the user makes a request the whole
	database, not just what is locally stored, needs to be
	processed. i think this is where database systems comes
	into play. for now, how about we store all the info in
	the database as follows: the first 

*/
