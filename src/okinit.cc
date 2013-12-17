/*
 * okinit.cc
 * A test program used to create the initial setting for okshell
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

#include "globals.h"
#include "command_profile.h"
#include "config.h"

namespace okshell
{
namespace detail
{
void init()
{
    CommandProfile profile;
    profile.write_to_file(kProfileLocal);
    profile.write_to_file(kProfileCloudDemo);
    ConfigFile config{};
    config.write_to_disk(kConfigFile);
}
} // end namespace detail
using detail::init;
} // end namespace okshell

int main()
{
    okshell::init();
}
