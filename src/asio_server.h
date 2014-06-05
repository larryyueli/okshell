/*
 * asio_server.h
 * Server class for cloud communication
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

#ifndef ASIO_SERVER_H_
#define ASIO_SERVER_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>

#include "common_defs.h"
#include "connection.h"
#include "connection_manager.h"
#include "request_handler.h"

namespace okshell
{
class AsioServer
{
public:
    explicit AsioServer(const std::string& address, const std::string& port);
    
private:
    // The io_service used to perform async operations
    boost::asio::io_service         io_serv_;
    // The signal_set is used to register for process termination notifications
    boost::asio::signal_set         signals_;
    // Acceptor used to listen for incoming connections
    boost::asio::ip::tcp::acceptor  acceptor_;
    // The connection manager which owns all live connections
    ConnectionManager               manager_;
    // The next socket to be accpeted
    boost::asio::ip::tcp::socket    sock_;
    // The handler for all incoming requests
    RequestHandler                  req_handler_;
    
public:
    // Run the server's io_service loop
    void run();
    
private:
    // Perform an async accept operation
    void do_accept();
    // Wait for a request to stop the server
    void do_await_stop();
    // The io_service used to perform async operations
    
public:
    DISALLOW_COPY_AND_ASSIGN(AsioServer)
};

} // end namespace okshell

#endif /* ASIO_SERVER_H_ */
