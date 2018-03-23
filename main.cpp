#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "Database.h"

enum Mode {
	Input,
	Query
};

Database* db;
int import_size;
bool imported;

/* get the number of data entries in_file, where each such entry is separated by a newline */
int get_num_lines(ifstream& in_file) {
	int count = 0;
	string str;
	while (getline(in_file, str))
		count++;
	return count;
}

/* copy a certain subset of the file to the process space */
void copy_file_to_here(ifstream& in_file, int partial_offset) {
	int offset;
	if (!imported) {
		offset = 0;
		imported = true;
	}
	else {
		offset = partial_offset + import_size;
	}

	for (int i = 0; i < offset; i++) {
		in_file.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	string line;
	while (getline(in_file, line))
		db->add_node(line);
}

int main(int argc, char* argv[]) {
	

	ofstream my_file;
	ifstream my_file_in;

	my_file_in.open("database.txt", ios::in);
	import_size = get_num_lines(my_file_in);
	my_file_in.close();

	imported = false;

	/* Default to writing */


	if (argc > 1 && strcmp(argv[1], "clean") == 0)
		my_file.open("database.txt", ios::out); //create a clean database. ONLY USED FOR TESTING
	else
		my_file.open("database.txt", ios::app); //append to existing database


	int pos_copy = 0;
	int num_added = 0;
	db = new Database();
	Mode mode = Input;
	string user_line;
	while(true) {
		if (mode == Input)
			cout << "Add: ";
		else
			cout << "Ask: ";


		getline(cin, user_line);
		if (user_line.compare("help") == 0) {
			cout << "Enter e to exit, otherwise enter some data and hit enter." << endl;
			cout << "Enter \"ask\" to query the database." << endl;
			cout << "Enter \"put\" to go back to inputting." << endl;
		}

		else if (user_line.compare("e") == 0) {
			my_file.close();
			break;
		}

		else if (user_line.compare("ask") == 0 && mode == Input) {
			mode = Query;
			my_file.close();
			my_file_in.open("database.txt", ios::in);
			copy_file_to_here(my_file_in, pos_copy);
			pos_copy = num_added;
		}

		else if (user_line.compare("put") == 0 && mode == Query) {
			mode = Input;
			my_file_in.close();
			my_file.open("database.txt", ios::app);
		}

		else if (mode == Input) {
			num_added++;
			my_file << user_line << endl;
		}

		else if (mode == Query) {
			Node* received = db->get_info(user_line);
			if (received == NULL) {
				cout << "No info found" << endl;
			}
			else {
				cout << "Here's what I found about " << user_line << ": " << endl;
				cout << received->data << endl;
			}
		}

		else {
			cout << "should never get here" << endl;
		}
	}

	my_file.close();
	my_file_in.close();
}


/*
	so when you start asking, when should the file on disk be
	imported in the program? every ask? hell no that would be very expensive
	requiring you to copy whole disk every time. instead on every ask
	you could copy from the last copied position.

	Ex:
	W:
	hello
	world
	ovi
	A: read from 1->3
	...
	...
	W:
	now
	write
	some
	more
	A: read from 4->7
	...
	...

	so everytime copy from a certain offset to eof
*/

