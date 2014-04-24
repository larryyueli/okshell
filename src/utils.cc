/*
 * utils.cpp
 *
 * Copyright (C) 2013  Larry Yueli Zhang
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "utils.h"

#include <sstream>
#include <cstdint> // for uint32_t
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/write.hpp>
#include <boost/lambda/lambda.hpp>
#include <arpa/inet.h>   // for ntohl() and htonl()

namespace utils
{
namespace detail
{
using std::string;
using std::vector;

typedef uint32_t        header_t;
// The size of the header prepended to each of string sent through socket
const size_t kHeaderSize = sizeof(header_t);
    
string lowercase(const string& s)
{
    string s2 = s;
    boost::to_lower(s2);
    return s2;
}

template <typename T>
string vec_str(const vector<T>& v)
{
    std::ostringstream oss;
    for (auto& s : v)
    {
        oss << s;
        oss << " ";
    }
    return oss.str();
}

// instantiation of the template function
template string vec_str<string>(const vector<string>& v);


string boldface(const string& s)
{
    return "\033[1m" + s + "\033[0m";
}

int exe_system(const string& command)
{
    return system(command.c_str());
}

bool contains_regex(const string& s, const string& re_str)
{
    boost::regex re{re_str};
    boost::match_results<std::string::const_iterator> m;
    return boost::regex_search(s, m, re);
}

bool contains_regex(const string& s, const boost::regex& re)
{
    boost::match_results<std::string::const_iterator> m;
    return boost::regex_search(s, m, re);
}

string get_home_dir()
{
    return string{getenv("HOME")};
}

string generate_uuid()
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    return boost::lexical_cast<string>(uuid);
}

boost::posix_time::time_duration milliseconds_to_boost(
        const std::chrono::milliseconds& ms)
{
    int64_t cnt = ms.count();
    return boost::posix_time::time_duration(0, 0, 0, cnt * 1000000);
}

void send_impl(boost::asio::ip::tcp::tcp::socket& sock, 
        const std::string& to_send, size_t total_size, 
        boost::system::error_code& ec)
{
    boost::asio::async_write(sock, boost::asio::buffer(to_send, total_size), 
            boost::lambda::var(ec) = boost::lambda::_1);
    return;
}

void send_wrapper(boost::asio::ip::tcp::tcp::socket& sock, 
        const std::string& message, boost::system::error_code& ec)
{
    size_t data_size = message.length();
    size_t total_size = data_size + kHeaderSize;
    string to_send =(total_size, '\0');
    
    header_t header = static_cast<header_t>(data_size);
    header = htonl(header); // resolve potential issue with endianness
    const char* header_str = reinterpret_cast<const char*>(&header);
    
    std::copy(header_str, header_str + kHeaderSize , to_send.begin());
    std::copy(message.data(), message.data() + data_size, 
            to_send.begin() + kHeaderSize);
    send_impl(sock, to_send, total_size, ec);
    return;
}

void receive_wrapper(boost::asio::ip::tcp::tcp::socket& sock, 
        std::string& message)
{
    
}

} // end namespace detail
} // end namespace utils

