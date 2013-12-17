/*
 * config_commander.cc
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

#include "config_commander.h"
#include <iostream>
#include "config_help_displayer.h"
#include "logger.h"

namespace okshell
{
namespace detail
{
using std::endl;
using std::cerr;

int ConfigCommander::process(const vector<string>& command) const
{
    cerr << "\n";
    // Condition for displaying the help
    if (command.size() == 0 || (command.size() == 1 && command[0] == "help"))
    {
        ConfigHelpDisplayer help{};
        help.display();
        return 0;
    }
    else if (command.size() == 2 
            && command[0] == "interactive" && command[1] == "off")
    {
        config_.set_interactive_off();
        mycerr << "Interactive OFF" << endl;
        return 0;
    }
    else if (command.size() == 2 
            && command[0] == "interactive" && command[1] == "on")
    {
        config_.set_interactive_on();
        mycerr << "Interactive ON" << endl;
        return 0;
    }
    else if (command.size() == 1 && command[0] == "userid")
    {
        mycerr << "You OkShell User ID is: " << config_.get_uuid() << endl;
    }
    else if (command.size() == 2 
            && command[0] == "cloud" && command[1] == "on")
    {
        config_.set_cloud_on();
        mycerr << "Cloud ON" << endl;
        return 0;
    }
    else if (command.size() == 2 
            && command[0] == "cloud" && command[1] == "off")
    {
        config_.set_cloud_off();
        mycerr << "Cloud OFF" << endl;
        return 0;
    }
    else
    {
        mycerr << "WARNING: unknown config command" << endl;
    }
    return 1;
}

} // end namespace detail
} // end namespace okshell



