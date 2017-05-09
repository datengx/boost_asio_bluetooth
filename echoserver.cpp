/* echoserver.cpp */
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
  void OnAccept(const std::string &mac_addr, uint8_t channel) {
    global_stream_lock.lock();
    std::cout << "[OnAccept] " << mac_addr << ":" << channel << "\n";
    global_stream_lock.unlock();

    Recv();
  }

  void OnConnect(const std::string &mac_addr, uint8_t channel) {
    global_stream_lock.lock();
    std::cout << "[OnConnect] " << mac_addr << ":" << channel << "\n";
    global_stream_lock.unlock();

    Recv();
  }

  void OnSend(const std::vector<uint8_t> & buffer) {
    global_stream_lock.lock();
    std::cout << "[OnSend] " << buffer.size() << " bytes\n";
    for(size_t x=0; x<buffer.size(); x++) {

      std::cout << (char)buffer[x];
      if((x + 1) % 16 == 0)
        std::cout << std::endl;
    }
    std::cout << std::endl;
    global_stream_lock.unlock();
  }

  void OnRecv(std::vector<uint8_t> &buffer) {
    global_stream_lock.lock();
    std::cout << "[OnRecv] " << buffer.size() << " bytes\n";
    for(size_t x=0; x<buffer.size(); x++) {

      std::cout << (char)buffer[x];
      if((x + 1) % 16 == 0)
        std::cout << std::endl;
    }
    std::cout << std::endl;
    global_stream_lock.unlock();

    // Start the next receive
    Recv();

    // Echo the data back
    Send(buffer);
  }

  void OnTimer(const boost::posix_time::time_duration &delta) {
    global_stream_lock.lock();
    std::cout << "[OnTimer] " << delta << "\n";
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

class MyAcceptor : public Acceptor {
private:
  bool OnAccept(boost::shared_ptr<Connection> connection, const std::string &addr, uint8_t channel) {
    global_stream_lock.lock();
    std::cout << "[OnAccept] " << addr << ":" << channel << "\n";
    global_stream_lock.unlock();

    return true;
  }

  void OnTimer(const boost::posix_time::time_duration &delta) {
    global_stream_lock.lock();
    std::cout << "[OnTimer] " << delta << "\n";
    global_stream_lock.unlock();
  }

  void OnError(const boost::system::error_code &error) {
    global_stream_lock.lock();
    std::cout << "[OnError] " << error << "\n";
    global_stream_lock.unlock();
  }

public:
  MyAcceptor(boost::shared_ptr<Hive> hive)
    : Acceptor(hive) {
  }

  ~MyAcceptor() {
  }
};

int main(void) {
  boost::shared_ptr<Hive> hive(new Hive());

  boost::shared_ptr<MyAcceptor> acceptor(new MyAcceptor(hive));
  // Listen on connection from anyone
  acceptor->Listen(13);

  boost::shared_ptr<MyConnection> connection(new MyConnection(hive));
  acceptor->Accept(connection);

  while(1) {
    hive->Poll();
    boost::this_thread::sleep( boost::posix_time::seconds(1) );
  }

  hive->Stop();

  return 0;
}
