#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <vector>


struct Node {
	std::string data;
};

class Database {
	public:
		Database() {};
		void add_node(std::string node);
		void print_nodes();
		struct Node* get_info(std::string query);

	private:
		std::vector<Node*> nodes;
};

#endif