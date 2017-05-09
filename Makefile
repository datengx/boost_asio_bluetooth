TARGETS=echoserver echoclient

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


echoserver:
	g++ -Wall -fpermissive -std=c++14 $(INC) wrapper.cpp echoserver.cpp -o echoserver $(SIMPLE_LIBS)
	mv $@ ./bin

echoclient:
	g++ -Wall -fpermissive -std=c++14 $(INC) wrapper.cpp echoclient.cpp -o echoclient $(SIMPLE_LIBS)
	mv $@ ./bin
