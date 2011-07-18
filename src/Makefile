

LIBS = -lcv -lcxcore -lhighgui
CFLAGS = -Wall -g $(LIBS)

all: algotest


algotest: algotest.c
	g++ $(CFLAGS) -o algotest algotest.c


testrun: algotest
	./algotest


clean:
	rm algotest

