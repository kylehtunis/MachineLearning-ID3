#ifndef ID3__H
#define ID3__H

#include <iostream>
#include <vector>
#include "Classifier.h"
#include "DataSet.h"
#include "Node.h"

using namespace std;

class ID3 : public Classifier {
private:
	Node* root;
	void train(DataSet&ds, Node* &n);
	int classify(Example& ex, Node*&);
public:
	ID3();
	ID3(DataSet&);
	virtual void train(DataSet& ds);
	virtual vector<int> classify(DataSet& ds);
	virtual int classify(Example& ex);
	~ID3();
};





#endif // !ID3__H
