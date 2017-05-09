//
//  asio_bluetooth/detail/endpoint.hpp
//  author: Da Teng
//  email: dan0702@g.ucla.edu
//


#ifndef BOOST_ASIO_BLUETOOTH_DETAIL_ENDPOINT_HPP
#define BOOST_ASIO_BLUETOOTH_DETAIL_ENDPOINT_HPP

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/winsock_init.hpp>
#include <boost/system/error_code.hpp>


#include <cstddef>
#include <string>

// misc, type definitions
#include "../misc.hpp"

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace bluetooth {
namespace detail {

class endpoint
{
public:
  // Default constructor
  endpoint()
    : data_()
  {
    data_.bt.rc_family = AF_BLUETOOTH;
    data_.bt.rc_bdaddr = *BDADDR_ANY;
    data_.bt.rc_channel = (uint8_t) 1;
    // TODO can we figure out the BT mac of the local host?
    mac_ = "[BDADDR_ANY]";
  }

  endpoint(uint8_t channel)
    : data_()
  {
    data_.bt.rc_family = AF_BLUETOOTH;
    data_.bt.rc_bdaddr = *BDADDR_ANY;
    data_.bt.rc_channel = (uint8_t) channel;
    // TODO can we figure out the BT mac of the local host?
    mac_ = "[BDADDR_ANY]";
  }

  // Construct endpoint using bt MAC address and channel number
  endpoint(const char* mac_addr, uint8_t channel)
    : data_()
  {
    data_.bt.rc_family = AF_BLUETOOTH;
    char addr[18];
    memcpy(addr, mac_addr, 18);
    str2ba( addr, &data_.bt.rc_bdaddr );
    data_.bt.rc_channel = (uint8_t) channel;

    mac_ = std::string(mac_addr);
  }

  // Constructor using std::string
  endpoint(const std::string& mac_addr, uint8_t channel)
    : data_()
  {
    data_.bt.rc_family = AF_BLUETOOTH;
    char addr[18];
    memcpy(addr, mac_addr.c_str(), 17);
    addr[17] = 0;
    str2ba( addr, &data_.bt.rc_bdaddr );
    data_.bt.rc_channel = (uint8_t) channel;

    mac_ = mac_addr;
  }

  // Copy Constructor
  endpoint(const endpoint& other)
    : data_(other.data_)
  {
  }

  // Assigned from another endpoint
  endpoint& operator=(const endpoint& other)
  {
    data_ = other.data_;
    return *this;
  }

  // Get the underlying endpoint in the native type
  boost::asio::detail::socket_addr_type* data()
  {
    return &data_.base;
  }

  // Get the underlying endpoint in the native type
  const boost::asio::detail::socket_addr_type* data() const
  {
    return &data_.base;
  }

  // Get the underlying size of the endpoint in the native type
  std::size_t size() const
  {
    return sizeof(boost::asio::detail::sockaddr_bt_type);
  }

  // Set the underlying size of the endpoint in the native type
  void resize(std::size_t new_size)
  {
    if (new_size > sizeof(boost::asio::detail::sockaddr_storage_type))
    {
      boost::system::error_code ec(boost::asio::error::invalid_argument);
      boost::asio::detail::throw_error(ec);
    }
  }

  // Get the capacity of the endpoint in the native type
  std::size_t capacity() const
  {
    return sizeof(boost::asio::detail::sockaddr_bt_type);
  }

  // Get Bluetooth MAC address
  std::string address() const
  {
    // TODO: convert directly from the address structure
    return mac_;
  }

  // Get the Bluetooth channel
  uint8_t channel() const
  {
    return (uint8_t) data_.bt.rc_channel;
  }

private:
  union data_union
  {
    // base address type for most of the address types
    // struct sockaddr
    boost::asio::detail::socket_addr_type base;
    boost::asio::detail::sockaddr_bt_type bt;
  } data_;

  std::string mac_;
};


} // namespace detail
} // namespace bluetooth
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

// implementation details
#include "./impl/endpoint.ipp"

#endif
