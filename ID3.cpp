#include "ID3.h"

ID3::ID3() {
	root = NULL;
}

ID3::ID3(DataSet& ds) {
	train(ds, root);
}

void ID3::train(DataSet& ds, Node* &n) {
	double entropy = ds.entropy();
	vector< vector < DataSet > > sets(ds.getAttributes().getSize()-1); //attribute, value
	double maxGain = 0;
	int maxNdx = -1;
	bool isHomogenous = true;
	int firstValue = ds.getExamples()[0][ds.getAttributes().getSize() - 1];
	for (int i = 1; i < ds.getExamples().size(); i++) { //check if ds is homogenous
		if (ds.getExamples()[i][ds.getAttributes().getSize() - 1] != firstValue) {
			isHomogenous = false;
			break;
		}
	}
	if (isHomogenous) {
		n = new Node(firstValue);
		n->children.resize(0);
		//cout << "Added new leaf node: " << firstValue << endl;
		return;
	}
	for (int i = 0; i < sets.size(); i++) { 
		sets[i].resize(ds.getAttributes().get(i)->getSize(), ds.getAttributes());
	}
	for (int i = 0; i < ds.getExamples().size(); i++) { //partition the examples based on attribute values
		for (int j = 0; j < ds.getExamples()[i].size() - 1; j++) {
			sets[j][ds.getExamples()[i][j]].add(ds.getExamples()[i]);
		}
	}
	for (int i = 0; i < sets.size(); i++) { //calculate the maximum gain
		double sum = 0;
		for (int j = 0; j < sets[i].size(); j++) {
			double toAdd = sets[i][j].getExamples().size();
			toAdd /= ds.getExamples().size();
			toAdd *= sets[i][j].entropy();
			sum += toAdd;
		}
		double gain = entropy - sum;
		gain /= ds.getAttributes().get(i)->getSize();
		if (gain > maxGain) {
			maxGain = gain;
			maxNdx = i;
		}
	}
	n = new Node(maxNdx);
	n->children.resize(ds.getAttributes().get(maxNdx)->getSize());
	for (int j = 0; j < n->children.size(); j++) { //recurse onto children
		if (sets[maxNdx][j].getExamples().size()>0) {
			//cout << "Adding new node: " << maxNdx << endl;
			train(sets[maxNdx][j], n->children[j]);
		}
		else {
			int value = ds.getMode();
			n = new Node(value);
			n->children.resize(0);
			//cout << "Added new leaf node probabalistically: " << value << endl;
			return;
		}
	}
}

void ID3::train(DataSet& ds) {
	train(ds, root);
}

int ID3::classify(Example& ex, Node*& n) {
	if (n->children.size() == 0) {
		return n->attribute;
	}
	else {
		return classify(ex, n->children[ex[n->attribute]]);
	}
}

int ID3::classify(Example& ex) {
	return classify(ex, root);
}

vector<int> ID3::classify(DataSet &ds) {
	vector<int> results;
	for (int i = 0; i < ds.getExamples().size(); i++) {
		results.push_back(classify(ds.getExamples()[i]));
	}
	return results;
}

ID3::~ID3() {
	delete root;
}