/*
 * profile_writer.cc
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#include "profile_writer.h"

namespace okshell
{
namespace detail
{
    
ProfileWriter::ProfileWriter(const string& profile_name)
    : profile_name_(profile_name)
{}

bool ProfileWriter::consistency_check(const string& human_command, 
        const string& real_command) const
{
    // TODO, check if the numbers of arguments agree
    return true;
}

bool ProfileWriter::write_command(const string& human_command, 
        const string& real_command) const
{
    // TODO, implement the write
    return true;
}

} // end namespace detail
} // end namespace okshell
