//
// Kyle Tunis
// kht10@georgetown.edu
// Platform: Windows
// Language/Environment: g++, VS15
//
// In accordance with the class policies and Georgetown's Honor Code,
// I certify that, with the exceptions of the class resources and those
// items noted below, I have neither given nor received any assistance
// on this project.
//


#include "Main.h"

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> options(argc);
	for (int i = 0; i < argc; i++) {
		options[i] = argv[i];
	}
	TrainTestSets tts(options);
	Evaluator eval(tts, options);
	//cout << "Entropy = " << tts.getTrainingSet().entropy() << endl;
	ID3 id3;
	eval.evaluate(&id3);
	return 0;
}