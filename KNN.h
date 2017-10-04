#ifndef KNN__H
#define KNN__H

#include "Classifier.h"

class KNN : public Classifier {
private:
	DataSet instances;
	int k;
public:
	KNN(int k);
	KNN(vector<string>&);
	KNN(DataSet&, int);
	virtual void train(DataSet&);
	virtual int classify(Example &ex);
	virtual vector<int> classify(DataSet &ds);
};




#endif // !KNN__H
