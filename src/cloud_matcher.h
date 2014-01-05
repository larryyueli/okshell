/*
 * cloud_matcher.h
 * The matcher that matches with the cloud
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

#ifndef CLOUD_MATCHER_H_
#define CLOUD_MATCHER_H_

#include <string>
#include <vector>

#include "common_defs.h"
#include "command_profile.h"

namespace okshell
{

enum class CloudMatchResultType
{
    ERROR = 0, // error case 
    NONE,      // no match
    SURE,      // confident about match, can just run
    UNSURE     // less confident, need user confirmation
};

struct CloudMatchEntry
{
    std::vector<OkString>    human_command;
    std::vector<OkString>    real_command;
    std::vector<OkString>    human_profile;
    std::vector<OkString>    real_profile;
    
    // return the string of the human command, with args boldfaced.
    std::string color_str_human_command() const;
    // return the string of the real command, with args boldfaced.
    std::string color_str_real_command() const;
    // return the string of the human command, no boldface.
    std::string plain_str_human_command() const;
    // return the string of the real command, no boldface.
    std::string plain_str_real_command() const;
    
    // return the string of the human command, with args boldfaced.
    std::string color_str_human_profile() const;
    // return the string of the real command, with args boldfaced.
    std::string color_str_real_profile() const;
    // return the string of the human command, no boldface.
    std::string plain_str_human_profile() const;
    // return the string of the real command, no boldface.
    std::string plain_str_real_profile() const;
};

// This class contains the information by the current user at the interface, 
// which contains the following:
// - a flag indicating the result type
// - what the user typed in
// - the matched human command, with arguments replaced
// - the matched real command of current platform, arguments replaced
// mutiple result entries are sorted according to relevance 
struct CloudMatchResult
{
    CloudMatchResultType            flag;
    std::string                     user_command;
    std::vector<CloudMatchEntry>    match_results;
    
    void display_multiple() const;
};

class CloudMatcher
{
public:
    CloudMatcher(const std::string& profile_filename);
    
private:
    std::string         profile_filename_;
    CommandProfile      profile_;
    
public:
    void match(const std::vector<std::string>& command, 
            CloudMatchResult& result) const;
    
private:
    // match command agaginst profile entries
    // for cloud, only get unsure results
    void match_profile_entries(const std::vector<std::string>& command, 
            const std::vector<CommandProfileEntry>& entries, 
            std::vector<CommandProfileEntry>& unsure_matches) const;
    
    // return whether command is an unsure match of profile
    bool is_unsure_match(const std::vector<std::string>& command, 
            const std::vector<OkString>& profile) const;
    
    // Match the typed command with the profile entry, 
    // replace the <arg1>'s in profile with real arguments in typed command
    bool replace_arguments(const CommandProfileEntry& profile_entry, 
            const std::vector<std::string>& command, CloudMatchEntry& result_entry) const;
    
    // result is the indexes that contain args
    // each index could contain more than one args
    void find_arg_indexes(const std::vector<OkString>& profile, 
            std::vector<size_t>& result) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(CloudMatcher);
};

} // end namespace okshell

#endif /* CLOUD_MATCHER_H_ */
