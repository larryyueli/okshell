/*
 * config_commander.h
 * The class that executes a config command
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#ifndef CONFIG_COMMANDER_H_
#define CONFIG_COMMANDER_H_

#include <string>
#include <vector>
#include "common_defs.h"
#include "config.h"

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

class ConfigCommander
{
public:
    ConfigCommander(Config& config) : config_(config) {}
    
private:
    Config&         config_;
    
public:
    // returns the return value of the execution of the config command
    // 0 means success, 1 means fail
    int process(const vector<string>& command) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(ConfigCommander);
};

} // end namespace detail
} // end namespace okshell


#endif /* CONFIG_COMMANDER_H_ */
