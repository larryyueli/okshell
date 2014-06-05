/*
 * asio_server.cc
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

#include "asio_server.h"

#include <boost/system/system_error.hpp>
#include <utility>

#include "utils.h"

namespace okshell
{
using std::string;

bool Handler::handle(const std::string& message, std::string& response)
{
    std::cout << "Handler::handle: |" << message << "|" 
            << message.size()<< std::endl; 
    return false;
}

Session::Pointer Session::create(boost::asio::io_service& io_serv, 
        Handler::Pointer handler_ptr)
{
    return Session::Pointer (new Session(io_serv, handler_ptr));
}

Session::Session(boost::asio::io_service& io_serv, 
        Handler::Pointer handler_ptr)
    : sock_(io_serv),
      handler_ptr_(handler_ptr)
{}

boost::asio::ip::tcp::socket& Session::socket()
{
    return sock_;
}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    string message;
    std::cout << "Before receive_wrapper #1" << std::endl; // TEMP
    utils::receive_wrapper(sock_, message, 
            [&, this](const boost::system::error_code& ec, size_t length)
            {
                if (!ec)
                {
                    string response;
                    bool will_respond = handler_ptr_->handle(message, response);
                    if (will_respond)
                    {
                        do_write(response);
                    }
                }
            });
    return;
}

void Session::do_write(const string& response)
{
    std::cout << "Base do_write" << std::endl;
}

AsioServer::AsioServer(int port, Handler::Pointer handler_ptr)
    : io_serv_{}, 
      acceptor_(io_serv_, boost::asio::ip::tcp::endpoint(
              boost::asio::ip::tcp::v4(), port)),
      sock_(io_serv_)
{
    do_accept();
}

void AsioServer::run()
{
    io_serv_.run();
}

void AsioServer::do_accept()
{
    Session::Pointer new_conn = Session::create(
            io_serv_, handler_ptr_);
    acceptor_.async_accept(new_conn->socket(), 
        [&](boost::system::error_code ec)
        {
            if (!ec)
            {
                new_conn->start();
                do_accept();
            }
        });
}

} // end namespace okshell
