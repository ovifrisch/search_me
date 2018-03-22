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

	private:
		std::vector<Node*> nodes;
};

#endif