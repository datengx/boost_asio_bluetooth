//
// asio_bluetooth/basic_endpoint.hpp
//
//
//

#ifndef BOOST_ASIO_BLUETOOTH_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_BLUETOOTH_BASIC_ENDPOINT_HPP

#include <boost/asio/detail/config.hpp>


#include "./detail/endpoint.hpp"

#include <boost/asio/detail/push_options.hpp>

namespace boost {

namespace asio {
namespace bluetooth {

template <typename Protocol>
class basic_endpoint
{
public:
  // Protocol type associated with the endpoint
  typedef Protocol protocol_type;

  basic_endpoint()
  {

  }

  basic_endpoint(const char* mac_addr)
  {
    
  }


};

} // namespace bluetooth
} // namespace asio
} // namespace boost



#include <boost/asio/detail/pop_options.hpp>
#endif
