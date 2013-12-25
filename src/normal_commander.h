/*
 * normal_commander.h
 * The class that executes a normal command
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

#ifndef NORMAL_COMMANDER_H_
#define NORMAL_COMMANDER_H_

#include <string>
#include <vector>
#include "local_matcher.h"
#include "cloud_matcher.h"
#include "config.h"

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

class NormalCommander
{
public:
    NormalCommander(Config& config)
    : config_(config),
      local_matcher_(kProfileLocal)
      //cloud_matcher_(kProfileCloudDemo)
{}
    
private:
    Config&         config_;
    LocalMatcher    local_matcher_;
    //CloudMatcher    cloud_matcher_;
    
public:
    // returns the return value of the execution of the command
    // input is the command vector without the leading "ok"
    // For example, {"recursively", "delete", "hpp", "files"}
    // The command is preprocesses with quoted entries combined
    // return value: 0 and 1 return value of actually run command
    // return 2 if didn't execute a command, and nothing new was learned
    // return 3 if didn't execute a command, but learned something
    int process(const vector<string>& command) const;
    
private:
    int process_interactive_on(const vector<string>& command) const;
    int process_interactive_off(const vector<string>& command) const;

    // when local match gives confident result
    // return return value of the command
    int process_local_sure(const LocalMatchResult& result, 
            bool interactive=true) const;
    
    // when local match result is confident
    // return return value of the command
    int process_local_unsure(const vector<string>& command, 
            const LocalMatchResult& result) const;
    
    // when not matching any command in local profile
    // return the return value of the command
    int process_local_none(const vector<string>& command) const;
    
    // Possible return values 2 and 3
    // for meaning  of return value, see the comment of process() function 
    int process_cloud(const vector<string>& command) const;
 
    // add the command manually, does not run it
    // always return 1
    int process_manual_add(const vector<string>& command) const;
    
    // add new command to local and sync with cloud
    void add_to_local_and_cloud(const string& human_command, 
            const string& real_command) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(NormalCommander);
};
    
} // end namespace detail
} // end namespace okshell

#endif /* NORMAL_COMMANDER_H_ */
