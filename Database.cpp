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