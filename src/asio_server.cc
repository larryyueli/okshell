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

namespace okshell
{

Session::Session(boost::asio::ip::tcp::socket socket)
    : sock_{std::move(socket)} {}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());
    sock_.async_read_some(boost::asio::buffer(data_, kMaxMsgLength), 
        [this, self](boost::system::error_code ec, size_t length)
        {
            if (!ec)
            {
                do_write(length);
            }
        });
}

void Session::do_write(size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(sock_, boost::asio::buffer(data_, length), 
        [this, self](boost::system::error_code ec, size_t /*length*/)
        {
            if (!ec)
            {
                do_read();
            }
        });
}

AsioServer::AsioServer(int port)
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
    acceptor_.async_accept(sock_, 
        [this](boost::system::error_code ec)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(sock_))->start();
            }
            do_accept();
        });
}

} // end namespace okshell
