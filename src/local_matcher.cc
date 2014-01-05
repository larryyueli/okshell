/*
 * local_matcher.cc
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

#include "local_matcher.h"

#include <sstream>
#include <iomanip>
#include <ostream>
#include <map>
#include <boost/algorithm/string/replace.hpp>
#include <utility>

#include "utils.h"
#include "okshell_utils.h"
#include "logger.h"
#include "globals.h"

namespace okshell
{
using std::ostringstream;
using std::setw;
using std::endl;
using std::map;
using std::pair;
using std::make_pair;
using std::string;
using std::vector;
using utils::vec_str;

string LocalMatchEntry::color_str_human() const
{
    return vec_str(vec_color(human_command));
}

string LocalMatchEntry::color_str_real() const
{
    return vec_str(vec_color(real_command));
}

string LocalMatchEntry::plain_str_human() const
{
    return vec_str(vec_plain(human_command));
}

string LocalMatchEntry::plain_str_real() const
{
    return vec_str(vec_plain(real_command));
}

void LocalMatchResult::display_multiple() const
{
    mycerr << "\n";
    for (size_t i = 0; i < match_results.size(); ++i)
    {
        size_t seq = i + 1;
        const auto& entry = match_results[i];
        mycerr << setw(3) << seq << ". " << os_label(kOSHuman) 
               << kEXE << " " << entry.color_str_human() << endl;
        mycerr << setw(5) << " " << os_label(kCurrentOS) 
               << entry.color_str_real() << "\n";
        mycerr << "\n";
     }
}

LocalMatcher::LocalMatcher(const string& profile_filename)
    : profile_filename_(profile_filename)
{
    profile_.load_from_file(profile_filename);
}

// for now just do simple linear search
// TODO, more sophisiticated data structures for matching
void LocalMatcher::match(const vector<string>& command, 
        LocalMatchResult& result) const
{
    result.user_command = vec_str(command);
    const auto& entries = profile_.get_entries();
    vector<pair<CommandProfileEntry, int32_t>> sure_matches{};
    vector<pair<CommandProfileEntry, int32_t>> unsure_matches{};
    match_profile_entries(command, entries, sure_matches, unsure_matches);
    if (!sure_matches.empty())
    {
        for (const auto& entry : sure_matches)
        {
            if (entry.second < 0)
            {
                throw OkShellException(
                        "LocalMatcher::match, entry.second < 0");
            }
            LocalMatchEntry result_entry{};
            if (replace_arguments(entry.first, command, result_entry))
            {
                result_entry.position = entry.second;
                result.match_results.push_back(result_entry);
            }
            else
            {
                throw OkShellException(
                "LocalMatcher::match, sure match failed argument replacement");
            }
        }
        size_t match_size = result.match_results.size();
        if (match_size == 1)
        {
             result.flag = LocalMatchResultType::SURE;
             return; // got one sure match, no need to check others.
        }
        else if (match_size > 1)
        {
            result.flag = LocalMatchResultType::UNSURE;
            // will continue checking unsure_matches
        }
        else // match_size == 0
        {
            throw OkShellException(
            "LocalMatcher::match, sure match no result, impossible");
        }
    }
    if (!unsure_matches.empty())
    {
        // Unsure matches could fail argument replacement, 
        // falied matches are not added the result, therefore
        // the returned result flag could be NONE
        
        for (const auto& entry : unsure_matches)
        {
            if (entry.second < 0)
            {
                throw OkShellException(
                        "LocalMatcher::match, entry.second < 0");
            }
            LocalMatchEntry result_entry{};
            if (replace_arguments(entry.first, command, result_entry))
            {
                result_entry.position = entry.second;
                result.match_results.push_back(result_entry);
            }
        }
    }
    if (!result.match_results.empty())
    {
        result.flag = LocalMatchResultType::UNSURE;
    }
    else
    {
        result.flag = LocalMatchResultType::NONE;
    }
    return;
}

void LocalMatcher::weak_match(const vector<string>& command, 
        LocalMatchResult& result) const
{
    result.user_command = vec_str(command);
    const auto& entries = profile_.get_entries();
    vector<pair<CommandProfileEntry, int32_t>> sure_matches{};
    vector<pair<CommandProfileEntry, int32_t>> unsure_matches{};
    match_profile_entries(command, entries, sure_matches, unsure_matches);
    if (!sure_matches.empty())
    {
        for (const auto& entry : sure_matches)
        {
            if (entry.second < 0)
            {
                throw OkShellException(
                        "LocalMatcher::match, entry.second < 0");
            }
            LocalMatchEntry result_entry{};
            if (replace_arguments(entry.first, command, result_entry))
            {
                result_entry.position = entry.second;
                result.match_results.push_back(result_entry);
            }
            else
            {
                throw OkShellException(
                "LocalMatcher::match, sure match failed argument replacement");
            }
        }
    }
    if (!unsure_matches.empty())
    {
        // Unsure matches could fail argument replacement, 
        // falied matches are not added the result, therefore
        // the returned result flag could be NONE
        for (const auto& entry : unsure_matches)
        {
            if (entry.second < 0)
            {
                throw OkShellException(
                        "LocalMatcher::match, entry.second < 0");
            }
            LocalMatchEntry result_entry{};
            if (replace_arguments(entry.first, command, result_entry))
            {
                result_entry.position = entry.second;
                result.match_results.push_back(result_entry);
            }
        }
    }
    if (!result.match_results.empty())
    {
        result.flag = LocalMatchResultType::UNSURE;
    }
    else
    {
        result.flag = LocalMatchResultType::NONE;
    }
    return;
}

void LocalMatcher::match_profile_entries(const vector<string>& command, 
        const vector<CommandProfileEntry>& entries, 
        vector<pair<CommandProfileEntry, int32_t>>& sure_matches,
        vector<pair<CommandProfileEntry, int32_t>>& unsure_matches) const
{
    size_t pos = 0;
    for (const auto& entry : entries)
    {
        const auto& human_profile = entry.human_profile_const();
        if (is_sure_match(command, human_profile))
        {
            sure_matches.push_back(make_pair(entry, pos));
            // Don't return here since one command can have 
            // several sure matches
        }
        else if (is_unsure_match(command, human_profile))
        {
            unsure_matches.push_back(make_pair(entry, pos));
        }
        ++pos;
    }
    return;
}

// current implementation: sure match is exact match, 
// i.e., everything other than the args are the exactly the same.
bool LocalMatcher::is_sure_match(const vector<string>& command, 
        const vector<OkString>& profile) const
{
    size_t command_size = command.size();
    if (profile.size() != command_size)
    {
        return false;
    }
    for (size_t i = 0; i < command_size; ++i)
    {
        if (profile[i].flag == OkStringType::CMD 
                && profile[i].impl != command[i])
        {
            return false;
        }
    }
    return true;
}

// current implementation: match if first word matches
// We now assume that the first word after ok is not an argument
// TODO, handle the case where the first word is argument
bool LocalMatcher::is_unsure_match(const vector<string>& command, 
        const vector<OkString>& profile) const
{
    return command[0] == profile[0].impl;
}

bool LocalMatcher::replace_arguments(const CommandProfileEntry& profile_entry, 
        const vector<string>& command, LocalMatchEntry& result_entry) const
{
    // Steps:
    // 1. get the indexes of args in human profile
    // 2. get corresponding substitute in command using the indexes, 
    //    therefore got a list of arg-sub pairs
    // 3. get a list of indexes containing args in real profile
    // 4. for each entry found above, perform replace for each arg-sub pair
    
    // Assumptions:
    // 1. human profile does not contain duplicate args
    // 2. arg in human profile is the whole word, blah<arg1> is not allowed
    // TODO, add checking to enforce this assumption
    
    // First copy the command in profile
    result_entry.human_command = profile_entry.human_profile_const();
    result_entry.real_command = profile_entry.real_profile_const();
    
    vector<size_t> indexes_human;
    find_arg_indexes(profile_entry.human_profile_const(), indexes_human);
    
    vector<size_t> indexes_real;
    find_arg_indexes(profile_entry.real_profile_const(), indexes_real);
    
    size_t command_size = command.size();
    for (size_t idx_human : indexes_human)
    {
        if (idx_human >= command_size)
        {
            return false;
        }
        const string& arg_str = profile_entry.human_profile_const()[idx_human].impl;
        const string& sub_str = command[idx_human];
        // first replace human command
        result_entry.human_command[idx_human].impl = sub_str;
        // then replace real command
        for (size_t idx_real : indexes_real)
        {
            boost::replace_all(result_entry.real_command[idx_real].impl, 
                    arg_str, sub_str);
        }
    }
    return true;
}

void LocalMatcher::find_arg_indexes(const vector<OkString>& profile, 
        vector<size_t>& result) const
{
    for (size_t i = 0; i < profile.size(); ++i)
    {
        if (profile[i].flag == OkStringType::ARG)
        {
            result.push_back(i);
        }
    }
    return;
}

} // end namespace okshell

