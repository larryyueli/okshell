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
#include <boost/algorithm/string/replace.hpp>
#include <utility>
#include "utils.h"
#include "okshell_utils.h"
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
               << kEXE << " " << entry.color_str_human_profile() << endl;
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
    result.user_command = vec_str(command);
    const auto& entries = profile_.get_entries();
    vector<CommandProfileEntry> unsure_matches{};
    match_profile_entries(command, entries, unsure_matches);
    if (!unsure_matches.empty())
    {
        for (const auto& entry : unsure_matches)
        {
            CloudMatchEntry result_entry{};
            result_entry.human_profile = entry.human_profile;
            result_entry.real_profile = entry.real_profile;
            if (replace_arguments(entry, command, result_entry))
            {
                result.match_results.push_back(result_entry);
            }
        }
    }
    if (!result.match_results.empty())
    {
        result.flag = CloudMatchResultType::UNSURE;
    }
    else
    {
        result.flag = CloudMatchResultType::NONE;
    }
    return;
}

void CloudMatcher::match_profile_entries(const vector<string>& command, 
        const vector<CommandProfileEntry>& entries, 
        vector<CommandProfileEntry>& unsure_matches) const
{
    for (const auto& entry : entries)
    {
        const auto& human_profile = entry.human_profile;
        if (is_unsure_match(command, human_profile))
        {
            unsure_matches.push_back(entry);
        }
    }
    return;
}

bool CloudMatcher::is_unsure_match(const vector<string>& command, 
        const vector<OkString>& profile) const
{
    return command[0] == profile[0].impl;
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
    
    size_t command_size = command.size();
    for (const auto& entry : arg_entries)
    {
        if (entry.index_human >= command_size)
        {
            return false;
        }
        const string& command_word = command[entry.index_human];
        result_entry.human_command[entry.index_human].impl = command_word;
        // replace all <arg1> with command_word
        // Note that in real command, <arg1> could be just part of a word
        // e.g., *.<arg1>
        boost::replace_all(result_entry.real_command[entry.index_real].impl, 
                entry.name, command_word);
    }
    return true;
}

// Assumptions, each word in real command only contains one <arg>,
// and each <arg> only appear once in real profile
// TODO, remove these assumptions
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
            string matched_part;
            if (!search_argument(word.impl, matched_part))
            {
                throw std::runtime_error(
                        "CloudMatcher::find_arg_indexes, ARG error 2");
            }
            name_lookup.at(matched_part).index_real = i;
        }
    }
    return;
}

} // end namespace detail
} // end namespace okshell
