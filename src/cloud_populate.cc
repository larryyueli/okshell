/*
 * cloud_populate.cc
 * A small program to populate the cloud profile for demo
 *
 * Copyright (C) 2013  Larry Yueli Zhang
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

#include <iostream>
#include "common_defs.h"
#include "keyboard_input.h"
#include "profile_writer.h"
#include "globals.h"
#include "logger.h"

namespace okshell
{
namespace detail
{
using std::endl;

const string kProfileCloudDemo = kConfigDir + "profile_cloud_demo";

void run()
{
    string human_command = command_input("Write the human command: $ ok");
    string real_command = command_input("Write the real command:  $");
    ProfileWriter profile_writer{kProfileCloudDemo};
    bool add_success = profile_writer.add_command_to_profile(
            human_command, real_command);
    mycerr << (add_success ? "Success." : "Failed") << endl;
    return;
}
} // end namespace detail
using detail::run;
} // end namespace okshell

int main()
{
    okshell::run();
    return 0;
}
