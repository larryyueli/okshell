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

#include <signal.h>
#include <utility>

namespace okshell
{
AsioServer::AsioServer(const std::string& address, const std::string& port)
    : io_serv_{},
      signals_{io_serv_},
      acceptor_{io_serv_},
      manager_{},
      sock_{io_serv_},
      req_handler_{}
{
    // Register to handle the signals that indicate when the server should exit
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
#if defined(SIGQUIT)
    signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
    
    do_await_stop();
    
    boost::asio::ip::tcp::resolver resolver{io_serv_};
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
    
    do_accept();
}

void AsioServer::run()
{
    io_serv_.run();
}

void AsioServer::do_accept()
{
    acceptor_.async_accept(sock_, 
            [this](boost::system::error_code error)
            {
                // Check whether the server was stopped by a signal before
                // this completion handler had a chance to run.
                if (!acceptor_.is_open())
                {
                    return;
                }
                if (!error)
                {
                    manager_.start(std::make_shared<Connection>(
                            std::move(sock_), manager_, req_handler_));
                }
                do_accept();
            });
}

void AsioServer::do_await_stop()
{
    signals_.async_wait(
            [this](boost::system::error_code /*error*/, int /*signo*/)
            {
                // The server is stopped by cancelling all outstanding async
                // operations. Once all operations have finished the 
                // io_service::run() call will exit
                acceptor_.close();
                manager_.stop_all();
            });
}

} // end namespace okshell
