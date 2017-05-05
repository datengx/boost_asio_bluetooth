/* pollwork.cpp */
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

int main(void) {
  boost::asio::io_service io_svc;
  boost::shared_ptr<boost::asio::io_service::work> worker(
    new boost::asio::io_service::work(io_svc)
  );

  worker.reset();

  io_svc.run();

  std::cout << "Hello World!" << std::endl;


  //for(int i=0; i<5; i++) {
  //  io_svc.poll();
  //  std::cout << "Line: " << i << std::endl;
  //}

  return 0;
}
