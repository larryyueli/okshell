/*
 * local_matcher.h
 * The matcher that matches local command profile.
 *
 *  Created on: 2013-11-20
 *      Author: Larry Yueli Zhang
 */

#ifndef LOCAL_MATCHER_H_
#define LOCAL_MATCHER_H_

#include <string>
#include <vector>
#include "common_defs.h"

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
    
    string repr_multiple() const;
};

class LocalMatcher
{
public:
    LocalMatcher(const string& profile_filename);
    
public:
    void match(const vector<string>& command, LocalMatchResult& result) const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(LocalMatcher);
};

} // end of namespace detail
} // end of namespace okshell

#endif /* LOCAL_MATCHER_H_ */
