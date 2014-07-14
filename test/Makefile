CC = g++
LIBS = -lcppunit -pthread

DEPS = ../comms/src
TESTDEPS = comms/src

%.o: %.cpp $(DEPS)/%cpp
	$(CC) -c -o $@ $< $(DEPS)/*.cpp

testrunner: MRTestRunner.o $(DEPS)/*.cpp 
	$(CC) -o testrunner MRTestRunner.o $(DEPS)/*.cpp $(TESTDEPS)/*.cpp $(LIBS)

clean:
	rm MRTestRunner.o


