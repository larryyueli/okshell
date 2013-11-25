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

string LocalMatchResult::repr_multiple() const
{
    ostringstream oss;
    for (size_t i = 0; i < match_results.size(); ++i)
    {
        int seq = i + 1;
        const auto& entry = match_results[i];
        oss << setw(3) << seq << ". " << entry.color_str_human() << "\n"
            << setw(5) << " " << "REAL: " << entry.color_str_real() << "\n\n";
    }
    return oss.str();
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
    for (auto& entry : profile_.get_entries())
    {
        // demo version: just match the first word
        if (entry.human_command[0].impl == word)
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
    result_entry.human_command = profile_entry.human_command;
    result_entry.real_command = profile_entry.real_command;
    
    vector<ArgEntry> arg_entries{};
    find_arg_indexes(profile_entry, arg_entries);
    
    for (const auto& entry : arg_entries)
    {
        result_entry.human_command[entry.index_human].impl = entry.name;
        result_entry.real_command[entry.index_real].impl = entry.name;
    }
    return true;
}

void LocalMatcher::find_arg_indexes(const CommandProfileEntry& profile_entry, 
        vector<ArgEntry>& result) const
{
    map<string, ArgEntry> name_lookup;
    // First round, populate the map with indexes in human_command
    for (size_t i = 0; i < profile_entry.human_command.size(); ++i)
    {
        const OkString& word = profile_entry.human_command[i];
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
    
    // Second round, add the indexes in real_command
    for (size_t i = 0; i < profile_entry.real_command.size(); ++i)
    {
        const OkString& word = profile_entry.real_command[i];
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
    return;
}

} // end namespace detail
} // end namespace okshell


