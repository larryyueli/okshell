/*
 * cloud_client.h
 * Client interface for communitcation with the cloud
 *
 * Copyright (C) 2014  Larry Yueli Zhang
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

#ifndef CLOUD_CLIENT_H_
#define CLOUD_CLIENT_H_

#include <iostream>
#include <string>
#include <chrono>
#include <boost/asio/connect.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

#include "common_defs.h"

namespace okshell
{
// A wrapper of a TCP client implemented using boost::asio
// Inspired by the boost::asio example of blocking tcp client with timeout
class AsioClient
{
public:
    // The ctor should estabish the TCP connection with the server
    AsioClient(const std::string& ip, const std::string& port);
    
private:
    boost::asio::io_service                 io_serv_;
    boost::asio::ip::tcp::tcp::socket       sock_;
    boost::asio::deadline_timer             deadline_;
    boost::asio::streambuf                  input_bufffer_;
    
public:
    // send out a string without waiting for a response
    // throw OkCloudException if error occurs or timeout reached
    void send(const std::string& str_to_send, 
            const std::chrono::milliseconds& timeout);
    // send out a request string and wait until a response string is received
    // throw OkCloudException if error occurs or timeout is reached
    void transact(const std::string& request, std::string& response, 
            const std::chrono::milliseconds& timeout);
    
private:
    // wait until a complete string is received from the socket
    // throw OkCloudException if error occurs
    // received is never really called publicly, so made private
    void receive(std::string& str_to_recv, const size_t& max_size, 
            const std::chrono::milliseconds& timeout);

private:
    DISALLOW_COPY_AND_ASSIGN(AsioClient);
};

} // end namespace okshell

#endif /* CLOUD_CLIENT_H_ */
