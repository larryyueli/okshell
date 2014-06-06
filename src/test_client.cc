/*
 * test_client.cc
 * tests for the client and server communication.
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

namespace okshell
{
using std::string;

void test()
{
    {
        AsioClient client{"localhost", "5678", std::chrono::milliseconds(2000)};
        //string req = "abcde";
        //std::cout << "Before sending:" << req << std::endl;
        string resp;
        client.transact("00000", resp);
        std::cout << "Response: " << resp << std::endl;
        client.transact("11111", resp);
        std::cout << "Response: " << resp << std::endl;
    }
    {
        AsioClient client{"localhost", "5678", std::chrono::milliseconds(2000)};
        //string req = "abcde";
        //std::cout << "Before sending:" << req << std::endl;
        string resp;
        client.transact("00000", resp);
        std::cout << "Response: " << resp << std::endl;
        client.transact("11111", resp);
        std::cout << "Response: " << resp << std::endl;
    }
    {
        AsioClient client{"localhost", "5678", std::chrono::milliseconds(2000)};
        //string req = "abcde";
        //std::cout << "Before sending:" << req << std::endl;
        string resp;
        client.transact("00000", resp);
        std::cout << "Response: " << resp << std::endl;
        client.transact("11111", resp);
        std::cout << "Response: " << resp << std::endl;
    }
    return;
}

} // end namespace okshell

int main(int argc, char **argv)
{
    okshell::test();
    return 0;
}
