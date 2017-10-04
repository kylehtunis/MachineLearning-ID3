#ifndef NAIVEBAYES__H
#define NAIVEBAYES__H

#include <iostream>
#include <vector>
#include "DataSet.h"
#include "Nominal.h"
#include "Classifier.h"

using namespace std;

class NaiveBayes : public Classifier {
private:
	vector<int> classCounts;
	vector<vector< vector<int> > > conditionalCounts; //(attribute, value, class value)
public:
	NaiveBayes();
	NaiveBayes(DataSet&);
	virtual void train(DataSet&);
	virtual int classify(Example&);
	virtual vector<int> classify(DataSet&);
};




#endif // !NAIVEBAYES__H
