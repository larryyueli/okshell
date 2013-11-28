/*
 * cloud_matcher.cc
 *
 *  Created on: 2013-11-22
 *      Author: ylzhang
 */

#include "cloud_matcher.h"
#include <sstream>
#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <map>
#include <utility>
#include "utils.h"
#include "globals.h"
#include "logger.h"

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

string CloudMatchEntry::color_str_human_command() const
{
    return vec_str(vec_color(human_command));
}

string CloudMatchEntry::color_str_real_command() const
{
    return vec_str(vec_color(real_command));
}

string CloudMatchEntry::plain_str_human_command() const
{
    return vec_str(vec_plain(human_command));
}

string CloudMatchEntry::plain_str_real_command() const
{
    return vec_str(vec_plain(real_command));
}

string CloudMatchEntry::color_str_human_profile() const
{
    return vec_str(vec_color(human_profile));
}

string CloudMatchEntry::color_str_real_profile() const
{
    return vec_str(vec_color(real_profile));
}

string CloudMatchEntry::plain_str_human_profile() const
{
    return vec_str(vec_plain(human_profile));
}

string CloudMatchEntry::plain_str_real_profile() const
{
    return vec_str(vec_plain(real_profile));
}

void CloudMatchResult::display_multiple() const
{
    mycerr << "\n";
    for (size_t i = 0; i < match_results.size(); ++i)
    {
        int seq = i + 1;
        const auto& entry = match_results[i];
        mycerr << setw(3) << seq << ". " << os_label(kOSHuman)
               << entry.color_str_human_profile() << endl;
        mycerr << setw(5) << " " << os_label(kOSLinux)
               << entry.color_str_real_profile() << "\n";
        mycerr << "\n";
     }
}

CloudMatcher::CloudMatcher(const string& profile_filename)
    : profile_filename_(profile_filename)
{
    profile_.load_from_file(profile_filename);
}

// for now just do simple linear search
// TODO, more sophisiticated matching algorthms
void CloudMatcher::match(const vector<string>& command, 
        CloudMatchResult& result) const
{
    const string& word = command[0];
    for (auto& entry : profile_.get_entries())
    {
        // demo version: just match the first word
        if (entry.human_profile[0].impl == word)
        {
            CloudMatchEntry result_entry{};
            result_entry.human_profile = entry.human_profile;
            result_entry.real_profile = entry.real_profile;
            bool success = replace_arguments(entry, command, result_entry);
            if (!success)
            {
                throw std::runtime_error(
                        "CloudMatcher::match, argument replacement failed");
            }
            result.match_results.push_back(result_entry);
        }
    }
    result.user_command = vec_str(command);
    size_t match_result_size = result.match_results.size();
    if (match_result_size == 0)
    {
        result.flag = CloudMatchResultType::NONE;
    }
    else
    {
        result.flag = CloudMatchResultType::UNSURE;
    }
    return;
}

bool CloudMatcher::replace_arguments(const CommandProfileEntry& profile_entry, 
        const vector<string>& command, CloudMatchEntry& result_entry) const
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
        result_entry.human_command[entry.index_human].impl = entry.name;
        result_entry.real_command[entry.index_real].impl = entry.name;
    }
    return true;
}

void CloudMatcher::find_arg_indexes(const CommandProfileEntry& profile_entry, 
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
                        "CloudMatcher::find_arg_indexes, ARG error 1");
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
                        "CloudMatcher::find_arg_indexes, ARG error 2");
            }
            name_lookup.at(word.impl).index_real = i;
        }
    }
    return;
}

} // end namespace detail
} // end namespace okshell
