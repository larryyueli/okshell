/*
 * config_commander.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
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
    else if (command[0] == "interactive" && command[1] == "off")
    {
        config_.set_interactive_off();
        mycerr << "Interactive OFF" << endl;
        return 0;
    }
    else if (command[0] == "interactive" && command[1] == "on")
    {
        config_.set_interactive_on();
        mycerr << "Interactive ON" << endl;
        return 0;
    }
    return 1;
}

} // end namespace detail
} // end namespace okshell



