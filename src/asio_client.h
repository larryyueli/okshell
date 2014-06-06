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
#include <array>
#include <boost/asio/connect.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "common_defs.h"
#include "globals.h"

namespace okshell
{
// A wrapper of a TCP client implemented using boost::asio
// Inspired by the boost::asio example of blocking tcp client with timeout
// AsioClient always expects a response from the server, and it waits
// until the timeout is reached.
class AsioClient
{
public:
    // The ctor should estabish the TCP connection with the server
    // Timeout = 0 means no timeout, i.e., wait forever
    AsioClient(const std::string& host, const std::string& port, 
            const std::chrono::milliseconds& timeout);
    ~AsioClient();
    
private:
    std::string         host_;
    std::string         port_;
    
    // We convert the chrono::milliseconds to boost time_duration
    // on construction and keep the boost format, to avoid too many
    // conversions since most of the places are using the boost type. 
    // In current implementation, this timeout is shared by connect()
    // send() and receive(), since this covers most of the use cases.
    // In the future we can add customized timeout for different functions.
    boost::posix_time::time_duration        timeout_;
    boost::asio::io_service                 io_serv_;
    boost::asio::ip::tcp::socket            sock_;
    boost::asio::deadline_timer             deadline_;
    // The buffer used for receiving response from the server
    // TODO: change to dynamic sized buffer for receiving large response
    std::array<char, kClientBufferSize>     buffer_;
    std::string                             response_;
    
public:
    // send out a request string and wait until a response string is received
    // throw OkCloudException if error occurs or timeout is reached
    void transact(const std::string& request, std::string& response);
    
    // close the TCP connection to the server
    void close();
    
private:
    // Connect the socket to the server at host:port
    void connect(const std::string& host, const std::string& port);
    // send out a string without waiting for a response
    // throw OkCloudException if error occurs or timeout reached
    void send(const std::string& req);
    // wait until a complete string is received from the socket
    // throw OkCloudException if error occurs
    // received is never really called publicly, so made private
    void receive(std::string& resp);
    
    // check whether the deadline has passed.
    void check_deadline();
    
public:
    DISALLOW_COPY_AND_ASSIGN(AsioClient);
};

} // end namespace okshell

#endif /* CLOUD_CLIENT_H_ */
