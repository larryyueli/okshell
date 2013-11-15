/*
 * config_commander.hpp
 * The class that executes a config command
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#ifndef CONFIG_COMMANDER_HPP_
#define CONFIG_COMMANDER_HPP_

#include <string>
#include <vector>

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

class ConfigCommander
{
public:
    ConfigCommander() {}
    
public:
    // returns the return value of the execution of the config command
    // 0 means success, 1 means fail
    int process(const vector<string>& command) const;
};
}
}


#endif /* CONFIG_COMMANDER_HPP_ */
