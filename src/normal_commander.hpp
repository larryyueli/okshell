/*
 * normal_commander.hpp
 * The class that executes a normal command
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#ifndef NORMAL_COMMANDER_HPP_
#define NORMAL_COMMANDER_HPP_

#include <string>
#include <vector>

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

class NormalCommander
{
public:
    NormalCommander() {}
    
public:
    // returns the return value of the execution of the command
    int process(const vector<string>& command) const;
};
    
} // end namespace detail
} // end namespace okshell


#endif /* NORMAL_COMMANDER_HPP_ */
