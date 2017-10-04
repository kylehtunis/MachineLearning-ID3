CPPS = $(wildcard *.cpp)
OBJS = ${CPPS:.cpp=.o}

all: Makefile.dep $(OBJS) NBMain.o KNNMain.o ID3Main.o
	g++ $(OBJS) NBMain.o -o NaiveBayes.exe
	g++ $(OBJS) KNNMain.o -o kNN.exe
	g++ $(OBJS) ID3Main.o -o ID3.exe

knn: Makefile.dep KNNMain.o
	g++ $(OBJS) KNNMain.o -o kNN.exe

nb: Makefile.dep $(OBJS) NBMain.o
	g++ $(OBJS) NBMain.o -o NaiveBayes.exe

id3: Makefile.dep $(OBJS) ID3Main.o
	g++ $(OBJS) ID3Main.o -o ID3.exe

$(OBJS): $(CPPS)
	g++ -c $(CPPS)

NBMain.o: NBMain.cc
	g++ -c NBMain.cc

KNNMain.o: KNNMain.cc
	g++ -c KNNMain.cc

ID3Main.o: ID3Main.cc
	g++ -c ID3Main.cc

depend:
	g++ -MM $(CPPS) KNNMain.cc NBMain.cc ID3Main.cc -o Makefile.dep

Makefile.dep:
	touch Makefile.dep

clean:
	rm kNN.exe NaiveBayes.exe ID3.exe *.o Makefile.dep

make: Makefile.dep $(OBJS) NBMain.o KNNMain.o ID3Main.o
	make kNN
	make nb
	make id3

include Makefile.dep