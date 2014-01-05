/*
 * config_commander.h
 * The class that executes a config command
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

#ifndef CONFIG_COMMANDER_H_
#define CONFIG_COMMANDER_H_

#include <string>
#include <vector>

#include "common_defs.h"
#include "config.h"

namespace okshell
{

class ConfigCommander
{
public:
    ConfigCommander(Config& config) : config_(config) {}
    
private:
    Config&         config_;
    
public:
    // returns the return value of the execution of the config command
    // 0 means success, 1 means fail
    int process(const std::vector<std::string>& command) const;
    
private:
    void process_remove_command() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(ConfigCommander);
};

} // end namespace okshell

#endif /* CONFIG_COMMANDER_H_ */
