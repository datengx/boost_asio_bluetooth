/* clienthttpget.cpp */
#include "wrapper.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

boost::mutex global_stream_lock;

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

class MyConnection : public Connection {
private:
  void OnAccept(const std::string &addr, uint8_t channel) {
    global_stream_lock.lock();
    std::cout << "[OnAccept] " << addr << ":" << channel << "\n";
    global_stream_lock.unlock();

    // Start the next receive
    Recv();
  }

  void OnConnect(const std::string &addr, uint8_t channel) {
    global_stream_lock.lock();
    std::cout << "[OnConnect] " << addr << ":" << channel << "\n";
    global_stream_lock.unlock();

    // Start the next receive
    Recv();

    std::string str = "hello world!";

    std::vector<uint8_t> request;
    std::copy(str.begin(), str.end(), std::back_inserter(request));
    Send(request);
  }

  void OnSend(const std::vector<uint8_t> &buffer) {
    global_stream_lock.lock();
    std::cout << "[OnSend] " << buffer.size() << " bytes\n";
    for(size_t x=0; x<buffer.size(); x++) {

      std::cout << (char)buffer[x];
      if((x + 1) % 16 == 0)
        std::cout << "\n";
    }
    std::cout << "\n";
    global_stream_lock.unlock();
  }

  void OnRecv(std::vector<uint8_t> &buffer) {
    global_stream_lock.lock();
    std::cout << "[OnRecv] " << buffer.size() << " bytes\n";
    for(size_t x=0; x<buffer.size(); x++) {

      std::cout << (char)buffer[x];
      if((x + 1) % 16 == 0)
        std::cout << "\n";
    }
    std::cout << "\n";
    global_stream_lock.unlock();

    // Start the next receive
    Recv();
  }

  void OnTimer(const boost::posix_time::time_duration &delta) {
    global_stream_lock.lock();
    std::cout << "[OnTimer] " << delta << std::endl;
    global_stream_lock.unlock();
  }

  void OnError(const boost::system::error_code &error) {
    global_stream_lock.lock();
    std::cout << "[OnError] " << error << "\n";
    global_stream_lock.unlock();
  }

public:
  MyConnection(boost::shared_ptr<Hive> hive)
    : Connection(hive) {
  }

  ~MyConnection() {
  }
};

int main(void) {
  boost::shared_ptr<Hive> hive(new Hive());

  boost::shared_ptr<MyConnection> connection(new MyConnection(hive));
  connection->Connect("60:57:18:7E:77:68", 1);

  while(1) {
    hive->Poll();
    boost::this_thread::sleep( boost::posix_time::seconds(1) );
  }

  hive->Stop();

  return 0;
}
