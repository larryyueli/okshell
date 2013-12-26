/*
 * profile_writer.cc
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

#include "profile_writer.h"
#include <iostream>
#include <set>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "command_profile.h"
#include "okshell_utils.h"
#include "logger.h"
#include "utils.h"

namespace okshell
{
using std::string;
using std::vector;
    
ProfileWriter::ProfileWriter(const string& profile_name)
    : profile_name_(profile_name)
{}

bool ProfileWriter::consistency_check(const string& human_command, 
        const string& real_command, string& error_message) const
{
    // check that human_command and real_command have the same arg strings
    try
    {
        std::set<string> args_human{};
        search_arguments(human_command, args_human);
        std::set<string> args_real{};
        search_arguments(real_command, args_real);
        if (args_human != args_real)
        {
            error_message 
                = "Human command and real command have different arguments"; 
            return false;
        }
    }
    catch (const OkShellException& e)
    {
        error_message = e.what();
        return false;
    }
    return true;
}

bool ProfileWriter::add_command_to_profile(const string& human_command, 
        const string& real_command) const
{
    string error_message{};
    bool consistent = consistency_check(human_command, real_command, 
            error_message);
    if (!consistent)
    {
        mycerr << utils::boldface("ERROR: ") << error_message << std::endl;
        return false;
    }
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
            profile_entry.human_profile.push_back(
                    OkString(OkStringType::ARG, s));
        }
        else
        {
            profile_entry.human_profile.push_back(
                    OkString(OkStringType::CMD, s));
        }
    }
    for (const auto& s : real_vec)
    {
        if (contains_argument(s))
        {
            profile_entry.real_profile.push_back(
                    OkString(OkStringType::ARG, s));
        }
        else
        {
            profile_entry.real_profile.push_back(
                    OkString(OkStringType::CMD, s));
        }
    }
    CommandProfile profile;
    profile.load_from_file(profile_name_);
    profile.add_entry(profile_entry);
    profile.write_to_file(profile_name_);
    return true;
}

void ProfileWriter::remove_command_from_profile(size_t pos) const
{
    CommandProfile profile;
    profile.load_from_file(profile_name_);
    profile.remove_entry(pos);
    profile.write_to_file(profile_name_);
    return;
}

} // end namespace okshell

