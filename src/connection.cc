/*
 * connection.cc
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

#include "connection.h"
#include <utility>
#include <vector>
#include <boost/system/system_error.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

#include "utils.h"
#include "connection_manager.h"
#include "request_handler.h"

namespace okshell
{
using std::string;
using utils::header_t;
using utils::kHeaderSize;

Connection::Connection(boost::asio::ip::tcp::socket sock, 
        ConnectionManager& manager, RequestHandler& req_handler)
    : sock_(std::move(sock)),
      manager_(manager),
      req_handler_(req_handler)
{}

void Connection::start()
{
    do_read();
}

void Connection::stop()
{
    sock_.close();
}

void Connection::do_read()
{
    auto self{shared_from_this()};
    boost::asio::async_read(sock_, boost::asio::buffer(buffer_, kHeaderSize), 
            [this, self](const boost::system::error_code& error, size_t length)
            {
                if (!error)
                {
                    assert(length == kHeaderSize);
                    string header_str{buffer_.data(), length};
                    size_t data_size = utils::interpret_header(header_str);
                    boost::asio::async_read(sock_, 
                        boost::asio::buffer(buffer_, data_size), 
                        [this, self](const boost::system::error_code& error2, 
                                size_t length2)
                        {
                            request_ = string{buffer_.data(), length2};
                            req_handler_.handle_request(request_, response_);
                            do_write();
                        });
                }
                else
                {
                    if (error != boost::asio::error::operation_aborted)
                    {
                        manager_.stop(shared_from_this());
                    }
                }
            });
}

void Connection::do_write()
{
    response_ = utils::add_header(response_);
    auto self{shared_from_this()};
    boost::asio::async_write(
            sock_, boost::asio::buffer(response_, response_.size()), 
            [this, self](const boost::system::error_code& error, size_t)
            {
                if (!error)
                {
                    do_read();
                }
                else
                {
                    if (error != boost::asio::error::operation_aborted)
                    {
                        manager_.stop(shared_from_this());
                    }
                }
            });
}

} // end namespace okshell

