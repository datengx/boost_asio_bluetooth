TARGETS=concurrent nonconcurrent unblocked poll multithreads ioservicebind

INC=$(shell pkg-config --cflags boost)

LIBS=$(shell pkg-config --libs boost)

all: rm_dir mk_dir $(TARGETS)

rm_dir:
	rm -rf ./bin

mk_dir:
	mkdir ./bin

nonconcurrent:
	g++ -Wall -ansi $(INC) nonconcurrent.cpp -o nonconcurrent $(LIBS)
	mv $@ ./bin

concurrent:
	g++ -Wall -ansi -std=c++11 $(INC) concurrent.cpp -o concurrent $(LIBS)
	mv $@ ./bin

unblocked:
		g++ -Wall -ansi -std=c++11 $(INC) unblocked.cpp -o unblocked $(LIBS)
		mv $@ ./bin

poll:
		g++ -Wall -ansi -std=c++11 $(INC) poll.cpp -o poll $(LIBS)
		mv $@ ./bin

multithreads:
		g++ -Wall -ansi -std=c++11 $(INC) multithreads.cpp -o multithreads $(LIBS)
		mv $@ ./bin

ioservicebind:
		g++ -Wall -ansi -std=c++11 $(INC) ioservicebind.cpp -o ioservicebind $(LIBS)
		mv $@ ./bin
