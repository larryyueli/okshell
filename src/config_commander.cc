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
#include <boost/algorithm/string/split.hpp> // boost::split
#include <boost/algorithm/string/classification.hpp> // boost::is_any_of
#include "config_help_displayer.h"
#include "logger.h"
#include "keyboard_input.h"
#include "local_matcher.h"

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
    else if (command.size() == 1 && command[0] == "remove")
    {
        process_remove_command();
    }
    else
    {
        mycerr << "WARNING: unknown config command" << endl;
    }
    return 1;
}

void ConfigCommander::process_remove_command() const
{
    mycerr << "\n";
    mycerr << "Write down the human command that you want to delete." << endl;
    mycerr << "For example, $ ok replace <1> with <2> in <3> files" << endl;
    string human_command = command_input("$ ok");
    mycerr << human_command << endl;
    // Assumption: there is no need to combine quoted entries since here
    // user is supposed to use <arg1> in the string
    // TODO: take care of quote signs
    vector<string> command;
    boost::split(command, human_command, boost::is_any_of(" "));
    LocalMatcher local_matcher{kProfileLocal};
    LocalMatchResult result;
    local_matcher.match(command, result);
    
    // only flags are possible here, UNSURE or NONE
    if (result.flag == LocalMatchResultType::UNSURE)
    {
        // TEMP, add impl
    }
    else if (result.flag == LocalMatchResultType::NONE)
    {
        // TEMP, add impl
    }
    else // ERROR or SURE, both impossible
    {
        throw std::runtime_error(
            "ConfigCommander::process_remove_command, ERROR or SURE");
    }
}

} // end namespace detail
} // end namespace okshell



