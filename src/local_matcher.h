/*
 * local_matcher.h
 * The matcher that matches local command profile.
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

#ifndef LOCAL_MATCHER_H_
#define LOCAL_MATCHER_H_

#include <string>
#include <vector>
#include "common_defs.h"
#include "command_profile.h"

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

enum class LocalMatchResultType
{
    ERROR = 0, // error case 
    NONE,      // no match
    SURE,      // confident about match, can just run
    UNSURE     // less confident, need user confirmation
};

struct LocalMatchEntry
{
    vector<OkString>    human_command;
    vector<OkString>    real_command;
    
    // return the string of the human command, with args boldfaced.
    string color_str_human() const;
    // return the string of the real command, with args boldfaced.
    string color_str_real() const;
    // return the string of the human command, no boldface.
    string plain_str_human() const;
    // return the string of the real command, no boldface.
    string plain_str_real() const;
};

// This class contains the information by the current user at the interface, 
// which contains the following:
// - a flag indicating the result type
// - what the user typed in
// - the matched human command, with arguments replaced
// - the matched real command of current platform, arguments replaced
// mutiple result entries are sorted according to relevance 
struct LocalMatchResult
{
    LocalMatchResultType        flag;
    string                      user_command;
    vector<LocalMatchEntry>     match_results;
    
    void display_multiple() const;
};

class LocalMatcher
{
public:
    LocalMatcher(const string& profile_filename);
    
private:
    string              profile_filename_;
    CommandProfile      profile_;
    
public:
    void match(const vector<string>& command, LocalMatchResult& result) const;
    
private:
    // match command agaginst profile entries
    void match_profile_entries(const vector<string>& command, 
            const vector<CommandProfileEntry>& entries, 
            vector<CommandProfileEntry>& sure_matches,
            vector<CommandProfileEntry>& unsure_matches) const;
    
    // return whether command is a sure match of profile
    bool is_sure_match(const vector<string>& command, 
            const vector<OkString>& profile) const;
    
    // return whether command is an unsure match of profile
    // may include sure match in the result
    bool is_unsure_match(const vector<string>& command, 
            const vector<OkString>& profile) const;
    
    // Match the typed command with the profile entry, 
    // replace the <arg1>'s in profile with real arguments in typed command
    bool replace_arguments(const CommandProfileEntry& profile_entry, 
            const vector<string>& command, LocalMatchEntry& result_entry) const;
    
    // result is the indexes that contain args
    // each index could contain more than one args
    void find_arg_indexes(const vector<OkString>& profile, 
            vector<size_t>& result) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(LocalMatcher);
};

} // end of namespace detail
} // end of namespace okshell

#endif /* LOCAL_MATCHER_H_ */
