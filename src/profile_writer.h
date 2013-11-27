/*
 * profile_writer.h
 * The class used to add a new command to the local profile
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#ifndef PROFILE_WRITER_H_
#define PROFILE_WRITER_H_

#include "common_defs.h"
#include "globals.h"

namespace okshell
{
namespace detail
{

class ProfileWriter
{
public:
    ProfileWriter(const string& profile_name=kProfileLocal);
    
private:
    string      profile_name_;
    
public:
    // Add the command mapping to local profile file
    // Input are strings with args, like "display <arg1> files"
    // Return whether the writing is successful.
    bool add_command_to_profile(const string& human_command, 
            const string& real_command) const;

private:
    // Return whether the human command and the real comand are 
    // consistent with each other, e.g., check if the human_command 
    // and the real_command have the same number of arguments
    bool consistency_check(const string& human_command, 
            const string& real_command) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(ProfileWriter);
};

} // end namespace detail
} // end namespace okshell

#endif /* PROFILE_WRITER_H_ */
