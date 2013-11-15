/*
 * normal_commander.cpp
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "normal_commander.hpp"

#include <iostream> // TEMP

namespace okshell
{
namespace detail
{
int NormalCommander::process(const vector<string>& command) const
{
    std::cout << "NormalCommander::process" << std::endl;
    return 0;
}

} // end namespace detail
} // end namespace okshell

