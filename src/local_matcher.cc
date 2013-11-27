/*
 * local_matcher.cc
 *
 *  Created on: 2013-11-20
 *      Author: Larry Yueli Zhang
 */

#include "local_matcher.h"
#include <sstream>
#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <map>
#include <utility>
#include "utils.h"
#include "logger.h"
#include "globals.h"

namespace okshell
{
namespace detail
{
using std::ostringstream;
using std::setw;
using std::endl;
using std::map;
using std::make_pair;
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
        int seq = i + 1;
        const auto& entry = match_results[i];
        mycerr << setw(3) << seq << ". " << os_label(kOSHuman) 
               << entry.color_str_human() << endl;
        mycerr << setw(5) << " " << os_label(kOSLinux) 
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
// TODO, more sophisiticated matching algorthms
void LocalMatcher::match(const vector<string>& command, 
        LocalMatchResult& result) const
{
    const string& word = command[0];
    const auto& entries = profile_.get_entries();
    for (const auto& entry : entries)
    {
        // demo version: just match the first word
        if (entry.human_profile[0].impl == word)
        {
            LocalMatchEntry result_entry{};
            bool success = replace_arguments(entry, command, result_entry);
            if (!success)
            {
                throw std::runtime_error(
                        "LocalMatcher::match, argument replacement failed");
            }
            result.match_results.push_back(result_entry);
        }
    }
    result.user_command = vec_str(command);
    size_t match_result_size = result.match_results.size();
    if (match_result_size == 0)
    {
        result.flag = LocalMatchResultType::NONE;
    }
    else if (match_result_size == 1)
    {
        result.flag = LocalMatchResultType::SURE;
    }
    else
    {
        result.flag = LocalMatchResultType::UNSURE;
    }
    return;
}

bool LocalMatcher::replace_arguments(const CommandProfileEntry& profile_entry, 
        const vector<string>& command, LocalMatchEntry& result_entry) const
{
    // Assume that the user typed command is the exactly the same 
    // as the human command in profile. So we just find the indexes 
    // of arguments and replace them.
    
    // First copy the command in profile
    result_entry.human_command = profile_entry.human_profile;
    result_entry.real_command = profile_entry.real_profile;
    
    vector<ArgEntry> arg_entries{};
    find_arg_indexes(profile_entry, arg_entries);
    
    for (const auto& entry : arg_entries)
    {
        result_entry.human_command[entry.index_human].impl 
            = command[entry.index_human];
        result_entry.real_command[entry.index_real].impl 
            = command[entry.index_human];
    }
    return true;
}

void LocalMatcher::find_arg_indexes(const CommandProfileEntry& profile_entry, 
        vector<ArgEntry>& result) const
{
    map<string, ArgEntry> name_lookup;
    // First round, populate the map with indexes in human_profile
    for (size_t i = 0; i < profile_entry.human_profile.size(); ++i)
    {
        const OkString& word = profile_entry.human_profile[i];
        if (word.flag == OkStringType::ARG)
        {
            if (!is_argument(word.impl))
            {
                throw std::runtime_error(
                        "LocalMatcher::find_arg_indexes, ARG error 1");
            }
            // Always add new entry since we assume each arg only appear once.
            // TODO, allow multiple appearance
            ArgEntry arg_entry;
            arg_entry.name = word.impl;
            arg_entry.index_human = i;
            name_lookup.insert(make_pair(arg_entry.name, arg_entry));
        }
    }
    
    // Second round, add the indexes in real_profile
    for (size_t i = 0; i < profile_entry.real_profile.size(); ++i)
    {
        const OkString& word = profile_entry.real_profile[i];
        if (word.flag == OkStringType::ARG)
        {
            if (!is_argument(word.impl))
            {
                throw std::runtime_error(
                        "LocalMatcher::find_arg_indexes, ARG error 2");
            }
            name_lookup.at(word.impl).index_real = i;
        }
    }
    // use the map to populate the result vector
    for (const auto& p : name_lookup)
    {
        result.push_back(p.second);
    }
    return;
}

} // end namespace detail
} // end namespace okshell


