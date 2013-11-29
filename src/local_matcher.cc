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
#include <boost/algorithm/string/replace.hpp>
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
               << kEXE << " " << entry.color_str_human() << endl;
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
// TODO, more sophisiticated data structures for matching
void LocalMatcher::match(const vector<string>& command, 
        LocalMatchResult& result) const
{
    result.user_command = vec_str(command);
    const auto& entries = profile_.get_entries();
    vector<CommandProfileEntry> sure_matches{};
    vector<CommandProfileEntry> unsure_matches{};
    match_profile_entries(command, entries, sure_matches, unsure_matches);
    if (!sure_matches.empty())
    {
        for (const auto& entry : sure_matches)
        {
            LocalMatchEntry result_entry{};
            if (replace_arguments(entry, command, result_entry))
            {
                result.match_results.push_back(result_entry);
            }
            else
            {
                throw std::runtime_error(
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
            throw std::runtime_error(
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
            LocalMatchEntry result_entry{};
            if (replace_arguments(entry, command, result_entry))
            {
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
        vector<CommandProfileEntry>& sure_matches,
        vector<CommandProfileEntry>& unsure_matches) const
{
    for (const auto& entry : entries)
    {
        const auto& human_profile = entry.human_profile;
        if (is_sure_match(command, human_profile))
        {
            sure_matches.push_back(entry);
            // Don't return here since one command can have 
            // several sure matches
        }
        else if (is_unsure_match(command, human_profile))
        {
            unsure_matches.push_back(entry);
        }
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
            string matched_part;
            if (!search_argument(word.impl, matched_part))
            {
                throw std::runtime_error(
                        "LocalMatcher::find_arg_indexes, ARG error 2");
            }
            name_lookup.at(matched_part).index_real = i;
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


