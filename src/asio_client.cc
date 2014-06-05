/*
 * cloud_client.cc
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

#include "asio_client.h"

#include <boost/system/system_error.hpp>

#include "globals.h"  // for kCloudIp, kCloudPort
#include "utils.h"    // for milliseconds_to_boost, send_wrapper, etc.

namespace okshell
{
using std::string;
using std::chrono::milliseconds;

AsioClient::AsioClient(const string& host, const string& port, 
        const milliseconds& timeout)
    : host_(host),
      port_(port), 
      timeout_(utils::milliseconds_to_boost(timeout)),
      io_serv_(), 
      sock_(io_serv_),
      deadline_(io_serv_)
{
    // No deadline is required untils the first socket operation is started.
    // We set the deadline to positive infinity so that the actor takes no 
    // action until a specific deadline is set.
    deadline_.expires_at(boost::posix_time::pos_infin);
    // Start the persistent actor that checks for deadline expiry.
    check_deadline();
    // connect to the server
    connect(host, port);
}

void AsioClient::send(const string& str_to_send)
{
    // For comments of the use of the boost::asio functions,
    // see that of the connect() function.
    deadline_.expires_from_now(timeout_);
    boost::system::error_code ec = boost::asio::error::would_block;
    utils::send_wrapper(sock_, str_to_send, 
            [&](const boost::system::error_code& error, size_t length)
            {
                std::cout << "send lambda" << std::endl; // TEMP
                ec = error;
            });
    do
    {
        io_serv_.run_one();
    } 
    while (ec == boost::asio::error::would_block);
    
    if (ec || !sock_.is_open())
    {
        throw boost::system::system_error(ec);
    }
    return;
}

void AsioClient::receive(string& str_to_recv)
{
    deadline_.expires_from_now(timeout_);
    boost::system::error_code ec = boost::asio::error::would_block;
    utils::receive_wrapper(sock_, str_to_recv, 
            [&](const boost::system::error_code& error, size_t length)
            {
                ec = error;
            });
    do
    {
        io_serv_.run_one();
    } 
    while (ec == boost::asio::error::would_block);
    
    if (ec || !sock_.is_open())
    {
        throw boost::system::system_error(ec);
    }
    return;
}

void AsioClient::transact(const string& request, string& response)
{
    send(request);
    receive(response);
}

void AsioClient::connect(const string& host, const string& port)
{
    // Resolve the host name and service to a list of endpoints.
    boost::asio::ip::tcp::resolver::query query{host, port};
    boost::asio::ip::tcp::resolver::iterator iter = 
            boost::asio::ip::tcp::resolver(io_serv_).resolve(query);
 
    // Set a deadline for the async operation, if a timeout is specified
    if (timeout_.total_milliseconds() != 0)
    {
        deadline_.expires_from_now(timeout_);
    }
    
    // Set up the variable that receives the result of the asynchronous
    // operation. The error code is set to would_block to signal that the
    // operation is incomplete. Asio guarantees that its asynchronous
    // operations will never fail with would_block, so any other value in
    // ec indicates completion.
    boost::system::error_code ec = boost::asio::error::would_block;
    
    // Start the asynchronous operation itself. The lambda function
    // object is used as a callback and will update the ec variable when the
    // operation completes.
    boost::asio::async_connect(sock_, iter, 
            [&](const boost::system::error_code& error, 
                boost::asio::ip::tcp::resolver::iterator)
                {
                    ec = error;
                });
    
    // Block until the asynchronous operation has completed.
    do
    {
        io_serv_.run_one();
    }
    while (ec == boost::asio::error::would_block);
    
    // Determine whether a connection was successfully established. The
    // deadline actor may have had a chance to run and close our socket, even
    // though the connect operation notionally succeeded. Therefore we must
    // check whether the socket is still open before deciding if we succeeded
    // or failed.
    if (ec || !sock_.is_open())
    {
        throw boost::system::system_error(ec);
    }
    return;
}

void AsioClient::disconnect()
{
    boost::system::error_code ignored_ec;
    sock_.close(ignored_ec);
    return;
}

void AsioClient::check_deadline()
{
    // We compare the deadline against the current time since a 
    // new async operation may have moved the deadline before this 
    // actor had a chance to run.
    if (deadline_.expires_at() <= 
            boost::asio::deadline_timer::traits_type::now())
    {
        // The deadline has passed. Close the socket so that any 
        // outstanding async operations are cancelled. This allows
        // the blocked connect(), receive() or send() to return.
        boost::system::error_code ignored_ec;
        sock_.close(ignored_ec);
        // There is no longer an active deadline. The expiry is set to 
        // positive infinity so that the actor takes no action until a
        // new deadline is set.
        deadline_.expires_at(boost::posix_time::pos_infin);
    }
    // Put the actor back to sleep
    //deadline_.async_wait(std::bind(&AsioClient::check_deadline, this));
    deadline_.async_wait(
            [this](const boost::system::error_code& error)
            {
                this->check_deadline();
            });
    return;
}

} // end namespace okshell
