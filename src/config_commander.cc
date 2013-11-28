/*
 * config_commander.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "config_commander.h"
#include "config_help_displayer.h"

namespace okshell
{
namespace detail
{
int ConfigCommander::process(const vector<string>& command) const
{
    // Condition for displaying the help
    if (command.size() == 0 || (command.size() == 1 && command[0] == "help"))
    {
        ConfigHelpDisplayer help{};
        help.display();
        return 0;
    }
    return 0;
}

} // end namespace detail
} // end namespace okshell



