/*
 * profile_writer.h
 * The class used to add a new command to the local profile
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

#ifndef PROFILE_WRITER_H_
#define PROFILE_WRITER_H_

#include "common_defs.h"
#include "globals.h"

namespace okshell
{
class ProfileWriter
{
public:
    ProfileWriter(const std::string& profile_name=kProfileLocal);
    
private:
    std::string      profile_name_;
    
public:
    // Add the command mapping to local profile file
    // Input are strings with args, like "display <arg1> files"
    // Return whether the writing is successful.
    bool add_command_to_profile(const std::string& human_command, 
            const std::string& real_command) const;
    
    // Remove a command mapping from local profile
    // command identified by its position in the current vector
    // Throw OkShellException if failed.
    void remove_command_from_profile(size_t pos) const;

private:
    // Return whether the human command and the real comand are 
    // consistent with each other, e.g., check if the human_command 
    // and the real_command have the same number of arguments
    bool consistency_check(const std::string& human_command, 
            const std::string& real_command, std::string& error_message) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(ProfileWriter);
};

} // end namespace okshell

#endif /* PROFILE_WRITER_H_ */
