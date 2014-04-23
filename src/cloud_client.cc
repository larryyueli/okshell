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

#include "cloud_client.h"

#include <boost/asio/read_until.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/write.hpp>
#include <boost/lambda/lambda.hpp>

#include "globals.h"  // for kCloudIp, kCloudPort
#include "utils.h"    // for milliseconds_to_boost

namespace okshell
{
using std::string;
using std::chrono::milliseconds;

AsioClient::AsioClient(const string& ip, const string& port)
    : io_serv_(), 
      sock_(io_serv_)
{
    boost::asio::ip::tcp::resolver resolver(io_serv_);
    boost::asio::connect(sock_, resolver.resolve({ip, port}));
}

void AsioClient::send(const std::string& str_to_send, 
        const milliseconds& timeout)
{
    size_t size_to_send = str_to_send.length();
    size_t size_sent = boost::asio::write(sock_, 
            boost::asio::buffer(str_to_send, size_to_send));
    if (size_sent != size_to_send)
    {
        throw OkCloudException("AsioClient::send, wrong size_sent");
    }
    return;
}

void AsioClient::receive(string& str_to_recv, const size_t& max_size, 
        const milliseconds& timeout)
{
    str_to_recv.clear(); // make sure the string is empty before receiving
    size_t resp_size = boost::asio::read(sock_, boost::asio::buffer(str_to_recv, 1));
}

} // end namespace okshell
