TARGETS=connectAsync serverAsync echoserver echoclient

INC=$(shell pkg-config --cflags boost) \
		-I/asio_bluetooth \


UNAME := $(shell uname)
LIBS=$(shell pkg-config --libs boost) \
		 -lbluetooth


# On Linux (not OSX) needs to manually link to pthread
ifeq ($(UNAME), Linux)
SIMPLE_LIBS=-L/usr/lib/x86_64-linux-gnu  -lboost_system -lboost_thread -lpthread \
						-lbluetooth
else ifeq($(UNAME), Darwin)
SIMPLE_LIBS=$LIBS
else
# do nothing for now
endif





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

dispatch:
		g++ -Wall -ansi -std=c++11 $(INC) dispatch.cpp -o dispatch $(LIBS)
		mv $@ ./bin

connectAsync:
		g++ -Wall -fpermissive -std=c++14 $(INC) connectAsync.cpp -o connectAsync $(SIMPLE_LIBS)
		mv $@ ./bin

serverAsync:
		g++ -Wall -fpermissive -std=c++14 $(INC) serverAsync.cpp -o serverAsync $(SIMPLE_LIBS)
		mv $@ ./bin

echoserver:
	g++ -Wall -fpermissive -std=c++14 $(INC) wrapper.cpp echoserver.cpp -o echoserver $(SIMPLE_LIBS)
	mv $@ ./bin

echoclient:
	g++ -Wall -fpermissive -std=c++14 $(INC) wrapper.cpp echoclient.cpp -o echoclient $(SIMPLE_LIBS)
	mv $@ ./bin
