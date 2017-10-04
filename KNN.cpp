#include "KNN.h"

KNN::KNN(int k) {
	this->k = k;
}

KNN::KNN(vector<string>& options) {
	for (int i = 1; i < options.size(); i++) {
		char c = options[i][1];
		switch (c) {
		case 'k':
			i++;
			k = atof(options[i].c_str());
			break;
		default:
			i++;
			break;
		}
	}
}

KNN::KNN(DataSet &ds, int kn) {
	instances = ds;
	k = kn;
}

int KNN::classify(Example& example) {
	vector<int> neighbors(k);
	vector<int> distances(k);
	for (int i = 0; i < k; i++) {
		neighbors[i] = -1;
		distances[i] = 100000000;
	}
	for (int i = 0; i < instances.getExamples().size(); i++) {
		int dist = 0;
		Example ex = instances.getExamples()[i];
		for (int j = 0; j < ex.size()-1; j++) {
			if (ex[j] != example[j]) {
				dist++;
			}
		}
		int min = 100000;
		int minDist = -1;
		for (int j = 0; j < k; j++) {
			if (neighbors[j] == -1) {
				neighbors[j] = i;
				distances[i] = dist;
				break;
			}
			else if (distances[j] > minDist && distances[j] > dist) {
				min = j;
				minDist = distances[j];
			}
		}
		if (min != 100000) {
			distances[min] = dist;
			neighbors[min] = i;
			cout << "";
		}
	}
	double max = 0;
	for (int i = 0; i < k; i++) {
		if (distances[i] > max) {
			max = distances[i];
		}
	}
	vector<double> classes(dynamic_cast<NominalAttribute*>(instances.getAttributes().getClassAttribute())->getSize());
	for (int i = 0; i < k; i++) {
		classes[instances.getExamples()[neighbors[i]][instances.getAttributes().getClassIndex()]] += ((1.0*distances[i]) / max);
	}
	max = -1;
	int maxNdx = -1;
	for (int i = 0; i < classes.size(); i++) {
		if (classes[i] > max) {
			max = classes[i];
			maxNdx = i;
		}
	}
	int distanceSum = 0;
	for (int i = 0; i < classes.size(); i++) {
		distanceSum += classes[i];
	}
	return maxNdx;
}

vector<int> KNN::classify(DataSet& ds) {
	vector<int> results(ds.getExamples().size());
	for (int i = 0; i < ds.getExamples().size(); i++) {
		results[i] = classify(ds.getExamples()[i]);
	}
	return results;
}

void KNN::train( DataSet& ds) {
	instances = ds;
}