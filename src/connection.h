/*
 * connection.h
 * The class of a TCP connection session at the server
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

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <array>
#include <string>
#include <memory>
#include <boost/asio/connect.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "common_defs.h"
#include "request_handler.h"
#include "globals.h"

namespace okshell
{
// forward declaration of ConnectionManager
class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    typedef std::shared_ptr<Connection>     Pointer;
    // Construct a connection with the given socket
    explicit Connection(boost::asio::ip::tcp::socket sock, 
            ConnectionManager& manager, RequestHandler& req_handler);

private:
    // Socket for the connection
    boost::asio::ip::tcp::socket            sock_;
    // The manager for this connection
    ConnectionManager&                      manager_;
    // The handler used to process the incoming request
    RequestHandler&                         req_handler_;
    // Buffer for incoming data
    std::array<char, kServerBufferSize>     buffer_;
    // The incoming request
    std::string                             request_;
    // The response to be sent to the client
    std::string                             response_;

public:
    // Start the first async operator for the connection
    void start();
    // Stop all async operations associated with this connection
    void stop();
    
private:
    // Perform an async read operation
    void do_read();
    // Perform an async write operation
    void do_write();
    
public:
    DISALLOW_COPY_AND_ASSIGN(Connection)
};
} // end namespace okshell

#endif /* CONNECTION_H_ */
