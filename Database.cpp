#include <iostream>
#include <string>
#include <vector>
#include "Database.h"
using namespace std;

void Database::add_node(string node) {

	struct Node* new_node= (Node*)malloc(sizeof(Node));
	new_node->data = node;
	nodes.push_back(new_node);
}

void Database::print_nodes() {
	for (int i = 0; i < nodes.size(); i++) {
		cout << nodes[i]->data << endl;
	}
}

struct Node* Database::get_info(string query) {

	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->data.substr(0, nodes[i]->data.length() - 1) == query) {
			if (nodes.size() > i) {
				return nodes[i + 1];
			}
		}
	}

	return NULL;
}
