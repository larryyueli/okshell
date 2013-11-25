/*
 * profile_writer.cc
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#include "profile_writer.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "command_profile.h"

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
    CommandProfileEntry profile_entry;
    vector<string> human_vec{};
    boost::split(human_vec, human_command, boost::is_any_of(" "), 
            boost::token_compress_on);
    vector<string> real_vec{};
    boost::split(real_vec, real_command, boost::is_any_of(" "), 
            boost::token_compress_on);
    for (const auto& s : human_vec)
    {
        if (is_argument(s))
        {
            profile_entry.human_command.push_back(
                    OkString(OkStringType::ARG, s));
        }
        else
        {
            profile_entry.human_command.push_back(
                    OkString(OkStringType::CMD, s));
        }
    }
    for (const auto& s : real_vec)
    {
        if (is_argument(s))
        {
            profile_entry.real_command.push_back(
                    OkString(OkStringType::ARG, s));
        }
        else
        {
            profile_entry.real_command.push_back(
                    OkString(OkStringType::CMD, s));
        }
    }
    CommandProfile profile;
    profile.load_from_file(profile_name_);
    profile.add_entry(profile_entry);
    profile.write_to_file(profile_name_);
    return true;
}

} // end namespace detail
} // end namespace okshell
