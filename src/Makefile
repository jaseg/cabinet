

LIBS = -lcv -lcxcore -lhighgui
CFLAGS = -Wall $(LIBS)

all: algotest-build testrun


algotest-build: algotest.c
	g++ $(CFLAGS) -o algotest algotest.c


testrun: algotest
	./algotest


clean:
	rm algotest

