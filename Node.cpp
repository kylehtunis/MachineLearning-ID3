#include "Node.h"
Node::Node() {
	children.resize(0);
}

Node::Node(int a) {
	attribute = a;
}

Node::~Node() {
	for (int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}