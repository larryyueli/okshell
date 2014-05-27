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
#include <memory>
#include <boost/asio.hpp>

#include "globals.h"

namespace okshell
{
// This server code is inspired by the async_tcp_echo_server 
// example provided in the documentation of boost::asio v1.55.0
class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket socket);
    
private:
    boost::asio::ip::tcp::socket    sock_;
    char                            data_[kMaxMsgLength];
    
public:
    void start();
    
private:
    void do_read();
    void do_write(size_t length);
};

class AsioServer
{
public:
    AsioServer(int port);
    
private:
    boost::asio::io_service         io_serv_;
    boost::asio::ip::tcp::acceptor  acceptor_;
    boost::asio::ip::tcp::socket    sock_;
    
public:
    void run();
    
private:
    void do_accept();
    
};
} // end namespace okshell

#endif /* ASIO_SERVER_H_ */
