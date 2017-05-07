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

  typedef boost::asio::detail::socket_addr_type data_type;

  basic_endpoint()
    : impl_()
  {
  }

  basic_endpoint(const char* mac_addr, uint8_t channel)
    : impl_(mac_addr, channel)
  {
  }

  basic_endpoint(const std::string& mac_addr, uint8_t channel)
    : impl_(mac_addr, channel)
  {
  }

  // Copy Constructor
  basic_endpoint(const basic_endpoint& other)
    : impl_(other.impl_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor
  basic_endpoint(basic_endpoint&& other)
    : impl_(other.impl_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another endpoint
  basic_endpoint& operator=(const basic_endpoint& other)
  {
    impl_ = other.impl_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign
  basic_endpoint& operator=(basic_endpoint&& other)
  {
    impl_ = other.impl_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  // The protocol associated with the endpoint
  protocol_type protocol() const
  {
    return protocol_type();
  }

  // Get the underlying endpoint in the native type
  data_type* data()
  {
    return impl_.data();
  }

  // Get the underlying endpoint in the native type
  const data_type* data() const
  {
    return impl_.data();
  }

  // Get the underlying size of the endpoint in the native type
  std::size_t size() const
  {
    return impl_.size();
  }

  // Set the underlying size of the endpoint in the native type
  void resize(std::size_t new_size)
  {
    impl_.resize(new_size);
  }

  // Get the capacity of the endpoint in the native type
  std::size_t capacity() const
  {
    return impl_.capacity();
  }

private:
  // underlying bluetooth endpoint
  boost::asio::bluetooth::detail::endpoint impl_;

};

/// Output an endpoint as a string
template <typename Elem, typename Traits, typename Procotol>
std::basic_ostream<Elem, Traits>& operator<<(
  std::basic_ostream<Elem, Traits>& os,
  const basic_endpoint<Procotol>& endpoint)
{
  os << "[ADD endpoint OSTREAM IMPLEMENTATION]";
  return os;
}



} // namespace bluetooth
} // namespace asio
} // namespace boost



#include <boost/asio/detail/pop_options.hpp>

#endif
