/*
 * config_commander.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "config_commander.h"

#include <iostream> // TEMP

namespace okshell
{
namespace detail
{
int ConfigCommander::process(const vector<string>& command) const
{
    std::cout << "ConfigCommander::process" << std::endl;
    return 0;
}

} // end namespace detail
} // end namespace okshell



