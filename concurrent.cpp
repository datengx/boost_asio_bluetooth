/* concurrent.cpp */
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void Print1() {
  for (int i=0; i<5; i++) {
    boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
    std::cout << "[Print1] Line: " << i << '\n';
  }
}

void Print2() {
  for (int i=0; i<5; i++) {
    boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
    std::cout << "[Print2] Line: " << i << '\n';
  }
}


int main(void) {
  boost::thread_group threads;
  // create two threads of work
  threads.create_thread(Print1);
  threads.create_thread(Print2);
  // join all the threads to allow all the work to finish
  threads.join_all();
}
