#ifndef NODE__H
#define NODE__H

#include <iostream>
#include <vector>
#include "DataSet.h"

using namespace std;

class Node {
public:
	int attribute;
	vector<Node*> children;
	Node(int);
	Node();
	~Node();
};



#endif // !NODE__H
