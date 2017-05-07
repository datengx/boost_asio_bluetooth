# boost_networking_bluetooth
This project extend the Boost ASIO functionality by adding bluetooth connection. More specifically, a `bluetooth` protocol class was added along with a bluetooth `endpoint` implementation. For more information regarding adding other types of protocol to the Boost ASIO library, check [this](http://www.boost.org/doc/libs/1_64_0/doc/html/boost_asio/overview/networking/other_protocols.html) link.

A simple, extensible echo server to demonstrate the Bluetooth communication is also included in the project.

### Prepare
To run the server/client pair, you need to prepare two Linux computers with Bluetooth function.

The echo server/client pair is based on the examples from

Boost.Asio C++ Network Programming - Second Edition by Wisnu Anggoro, John Torjo

To install the dependencies do the following:
##### Boost Library
```
sudo apt-get install libboost-all-dev
```
##### BlueZ
```
sudo apt-get install bluez
```
If you have older version of BlueZ installed, checkout [this](https://askubuntu.com/questions/662347/bluez-5-x-and-ubuntu-14-0x/662349) link.

### Build
```
make
```
### Run
Prepare two computers. Install this project on both of the computers. On one of the computers, in the project root directory, do:
```
./bin/echoserver
```

Then on the other computer, do
```
./bin/echoclient
```
in the project root directory.
