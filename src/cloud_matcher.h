/*
 * cloud_matcher.h
 * The matcher that matches with the cloud
 *
 *  Created on: 2013-11-22
 *      Author: Larry Yueli Zhang
 */

#ifndef CLOUD_MATCHER_H_
#define CLOUD_MATCHER_H_

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

enum class CloudMatchResultType
{
    ERROR = 0, // error case 
    NONE,      // no match
    SURE,      // confident about match, can just run
    UNSURE     // less confident, need user confirmation
};

struct CloudMatchEntry
{
    vector<OkString>    human_command;
    vector<OkString>    real_command;
    vector<OkString>    human_profile;
    vector<OkString>    real_profile;
    
    // return the string of the human command, with args boldfaced.
    string color_str_human_command() const;
    // return the string of the real command, with args boldfaced.
    string color_str_real_command() const;
    // return the string of the human command, no boldface.
    string plain_str_human_command() const;
    // return the string of the real command, no boldface.
    string plain_str_real_command() const;
    
    // return the string of the human command, with args boldfaced.
    string color_str_human_profile() const;
    // return the string of the real command, with args boldfaced.
    string color_str_real_profile() const;
    // return the string of the human command, no boldface.
    string plain_str_human_profile() const;
    // return the string of the real command, no boldface.
    string plain_str_real_profile() const;
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
    CloudMatchResultType        flag;
    string                      user_command;
    vector<CloudMatchEntry>     match_results;
    
    string repr_multiple() const;
};

class CloudMatcher
{
public:
    CloudMatcher(const string& profile_filename);
    
private:
    string              profile_filename_;
    CommandProfile      profile_;
    
public:
    void match(const vector<string>& command, CloudMatchResult& result) const;
    
private:
    // Match the typed command with the profile entry, 
    // replace the <arg1>'s in profile with real arguments in typed command
    // return value: whether the replacing was successful
    bool replace_arguments(const CommandProfileEntry& profile_entry, 
            const vector<string>& command, 
            CloudMatchEntry& result_entry) const;
    
    // given a command with <args>, find the indexes that have <args>
    void find_arg_indexes(const CommandProfileEntry& profile_entry, 
            vector<ArgEntry>& result) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(CloudMatcher);
};

} // end namespace detail
} // end namespace okshell

#endif /* CLOUD_MATCHER_H_ */
