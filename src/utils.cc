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
#include <boost/asio/read.hpp>
#include <arpa/inet.h>   // for ntohl() and htonl()

namespace utils
{
namespace detail
{
using std::string;
using std::vector;
    
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
    return boost::posix_time::time_duration(0, 0, 0, cnt * 1000);
}

void send_impl(boost::asio::ip::tcp::socket& sock, 
        const std::string& to_send, size_t total_size, 
        HandlerType handler)
{
    //std::cout << "send_impl" << std::endl;
    //string test_send = "abcd"; // TEMP
    //total_size = 4; // TEMP
    boost::asio::async_write(sock, boost::asio::buffer(to_send, total_size), 
            handler); // TEMP test_send -> to_send
    return;
}

void send_wrapper(boost::asio::ip::tcp::socket& sock, 
        const std::string& message, HandlerType handler)
{
    size_t data_size = message.length();
    size_t total_size = data_size + kHeaderSize;
    string to_send(total_size, '\0');
    
    header_t header = static_cast<header_t>(data_size);
    header = htonl(header); // resolve potential issue with endianness
    const char* header_str = reinterpret_cast<const char*>(&header);
        
    // Write the header
    std::copy(header_str, header_str + kHeaderSize , to_send.begin());
    // Write the body of the message
    std::copy(message.data(), message.data() + data_size, 
            to_send.begin() + kHeaderSize);
    // Send it off
    send_impl(sock, to_send, total_size, handler);
    return;
}

void receive_impl(boost::asio::ip::tcp::socket& sock,
        size_t recv_size, std::string& result, HandlerType handler)
{
    // Static buffer of size 4096 can handle most messages 
    // and avoid dynamic allocation
    //static const size_t BUFSIZE = 20;
    //static char static_buf[BUFSIZE + 1];
    //char actual_buf[20];
    vector<char> buf;
    buf.reserve(recv_size + 1);
    
    // allocate bigger buf if necessary
//    vector<char> big_buf;
//    char *actual_buf;
//    if (recv_size > 20)
//    {
//        // allocate big buf
//        big_buf.resize(recv_size + 1);
//        actual_buf = big_buf.data();
//    }
//    else
//    {
//        // just use buf
//        actual_buf = static_buf;
//    }
    //result.reserve(recv_size);
    result.clear();
    //::memset(actual_buf, '\0', recv_size + 1);
    std::cout << "Before async_read" << std::endl; // TEMP
    std::cout << "recv_size = " << recv_size << std::endl; // TEMP
    boost::asio::async_read(sock, boost::asio::buffer(buf, recv_size),
            [&](const boost::system::error_code& error, size_t length)
            {
                std::cout << "result: " << result << std::endl;
                std::cout << "receive_impl: lambda 1: " << length << std::endl; // TEMP
                //assert(recv_size == length);
                result.assign(buf.begin(), buf.end());
                assert(result.length() == length);
                std::cout << "receive_impl: before entering handler" << std::endl; // TEMP
                handler(error, length);
            });
    return;
}

void receive_wrapper(boost::asio::ip::tcp::socket& sock, 
        string& message, HandlerType handler)
{
    // Read the header
    string header_str;
    std::cout << "Before calling receive_impl #1" << std::endl; // TEMP
    std::cout << "kHeaderSize " << kHeaderSize << std::endl; // TEMP

    receive_impl(sock, kHeaderSize, header_str, 
            [&](const boost::system::error_code& error, size_t length)
            {
                // Interpret the header
                std::cout << "receive_impl: lambda 2" << std::endl; // TEMP
                header_t header;
                std::copy(header_str.data(), header_str.data() + kHeaderSize, 
                        reinterpret_cast<char*>(&header));
                header = ntohl(header); // resolve potential issue with endianness
                size_t data_size = static_cast<size_t>(header);
                std::cout << "data_size = " << data_size << std::endl; // TEMP
                std::cout << "Before calling receive_impl #2" << std::endl; // TEMP
                receive_impl(sock, data_size, message, handler);
            });
    return;
}

size_t interpret_header(const std::string& header_str)
{
    header_t header;
    std::copy(header_str.data(), header_str.data() + kHeaderSize, 
            reinterpret_cast<char*>(&header));
    header = ntohl(header); // resolve potential issue with endianness
    return static_cast<size_t>(header);
}

string add_header(const string& data_str)
{
    size_t data_size = data_str.length();
    size_t total_size = data_size + kHeaderSize;
    string result(total_size, '\0');
     
    header_t header = static_cast<header_t>(data_size);
    header = htonl(header); // resolve potential issue with endianness
    const char* header_str = reinterpret_cast<const char*>(&header);
     
    // Write the header
    std::copy(header_str, header_str + kHeaderSize , result.begin());
    // Write the body of the message
    std::copy(data_str.data(), data_str.data() + data_size, 
         result.begin() + kHeaderSize);
    return result;
}

} // end namespace detail
} // end namespace utils

