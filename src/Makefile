

LIBS = -lcv -lcxcore -lhighgui
CFLAGS = -Wall -g $(LIBS)

all: algotest-build


algotest-build: algotest.c
	g++ $(CFLAGS) -o algotest algotest.c


testrun: algotest
	./algotest


clean:
	rm algotest

