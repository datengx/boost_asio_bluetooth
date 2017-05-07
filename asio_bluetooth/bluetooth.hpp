//
// bluetooth.hpp
//
//
//
//

#ifndef BOOST_ASIO_BLUETOOTH_HPP
#define BOOST_ASIO_BLUETOOTH_HPP


#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/socket_acceptor_service.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>
// Bluetooth endpoint implementation
#include "basic_endpoint.hpp"

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace bluetooth {

/**
 *  The boost::asio::bluetooth contains class necessary for Bluetooth Sockets.
 *
 *
 */
class bluetooth
{
public:
  // Construct with a specific family
  bluetooth()
  {
  }

  // Obtain the type of the protocol, corresponding to the type argument
  // of POSIX socket()
  int type() const
  {
    return SOCK_STREAM;
  }


  // Obtain identifier of the protocol, corresponding to protocol argument
  // of POSIX socket()
  int protocol() const
  {
    return BTPROTO_RFCOMM;
  }


  // Obtain the identifier of the protocol family, corresponding to the
  // domain argument of POSIX socket()
  int family() const
  {
    return AF_BLUETOOTH;
  }

  // The Bluetooth endpoint type
  typedef boost::asio::bluetooth::basic_endpoint<bluetooth> endpoint;

  // The Bluetooth socket type.
  typedef basic_stream_socket<bluetooth> socket;

  // The Bluetooth acceptor type
  typedef basic_socket_acceptor<bluetooth> acceptor;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  typedef basic_socket_iostream<bluetooth> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)


};

} // namespace bluetooth
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif
