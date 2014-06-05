/*
 * utils.h
 * utilities and helpers that are independent of any specific project
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

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>
#include <chrono>
#include <boost/regex.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace utils
{
namespace detail
{

typedef std::function<void(const boost::system::error_code&, size_t)> HandlerType;

// convert a string to lower case and return it.
std::string lowercase(const std::string& s);

// return the string representation of a vector of Ts
template <typename T>
std::string vec_str(const std::vector<T>& v);

// return the ANSI escaped code of boldface string
std::string boldface(const std::string& s);

// run a system command, return the return value of the command
int exe_system(const std::string& command);

// return if a string contains a substring that matches regex
bool contains_regex(const std::string& s, const std::string& re_str);
bool contains_regex(const std::string& s, const boost::regex& re);

// get the path of home folder of current user
std::string get_home_dir();

// generate a uuid in string format
std::string generate_uuid();

// convert a value of chrono::millisecond type to 
// a boost::posix_time::time_duration type 
boost::posix_time::time_duration milliseconds_to_boost(
        const std::chrono::milliseconds& ms);

// send string to_send of size total_size through socket sock
// handler is the function to be called after sending is done.
void send_impl(boost::asio::ip::tcp::socket& sock, 
        const std::string& to_send, size_t total_size, 
        HandlerType handler);

// A wrapper funcion around the default async_write() in boost::asio,
// prepend to the message a header that indicates the length of the 
// string to send, and then send out the message with header.
void send_wrapper(boost::asio::ip::tcp::socket& sock, 
        const std::string& message, HandlerType handler);

// receive a string of recv_size from sock using input_buffer
// received string stored in result, error code updated in ec
void receive_impl(boost::asio::ip::tcp::socket& sock,
        size_t recv_size, std::string& result, HandlerType handler);

// A wrapper function around the default async_read() in boost::asio,
// first receives the header and decode the length of the message, 
// then receiving the whole message.
void receive_wrapper(boost::asio::ip::tcp::socket& sock, 
        std::string& message, HandlerType handler);

} // end namespace detail

using detail::lowercase;
using detail::vec_str;
using detail::boldface;
using detail::exe_system;
using detail::contains_regex;
using detail::get_home_dir;
using detail::generate_uuid;
using detail::milliseconds_to_boost;
using detail::send_wrapper;
using detail::receive_wrapper;

} // end namespace utils

#endif /* UTILS_H_ */
