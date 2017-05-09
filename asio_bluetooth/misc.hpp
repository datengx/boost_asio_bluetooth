//
//  asio_bluetooth/misc.hpp
//  author: Da Teng
//  email: dan0702@g.ucla.edu
//

#ifndef BOOST_ASIO_BLUETOOTH_MISC_HPP
#define BOOST_ASIO_BLUETOOTH_MISC_HPP

#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

namespace boost {
namespace asio {
namespace detail {

typedef sockaddr_rc sockaddr_bt_type;

} // namespace detail
} // namespace asio
} // namespace boost

#endif
