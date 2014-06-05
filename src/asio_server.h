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

#include "globals.h"
#include "common_defs.h"

namespace okshell
{
    
class Handler
{
public:
    typedef std::shared_ptr<Handler>        Pointer;
    
    Handler() {}
    virtual ~Handler() {}
    
public:
    // return value: whether to send a response
    // if to send a response, the value of is written in string response
    // if not to send a response, response should be empty and disregarded
    virtual bool handle(const std::string& message, std::string& response);

private:
    DISALLOW_COPY_AND_ASSIGN(Handler);
};

// This server code is inspired by the async_tcp_echo_server 
// example provided in the documentation of boost::asio v1.55.0
class Session : public std::enable_shared_from_this<Session>
{
public:
    typedef std::shared_ptr<Session>        Pointer;
    
    static Session::Pointer create(boost::asio::io_service& io_serv, 
            Handler::Pointer handler_ptr);
private:
    Session(boost::asio::io_service& io_serv, 
            Handler::Pointer handler_ptr);

private:
    boost::asio::ip::tcp::socket    sock_;
    Handler::Pointer            handler_ptr_;

public:
    boost::asio::ip::tcp::socket& socket();
    void start();
    
private:
    void do_read();
    void do_write(const std::string& response);
    
private:
    DISALLOW_COPY_AND_ASSIGN(Session);
};

class AsioServer
{
public:
    AsioServer(int port, Handler::Pointer handler_ptr);
    
private:
    boost::asio::io_service         io_serv_;
    boost::asio::ip::tcp::acceptor  acceptor_;
    boost::asio::ip::tcp::socket    sock_;
    Handler::Pointer            handler_ptr_;
    
public:
    void run();
    
private:
    void do_accept();
    
private:
    DISALLOW_COPY_AND_ASSIGN(AsioServer);
};

} // end namespace okshell

#endif /* ASIO_SERVER_H_ */
