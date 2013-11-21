/*
 * local_matcher.hpp
 * The matcher that matches local command profile.
 *
 *  Created on: 2013-11-20
 *      Author: Larry Yueli Zhang
 */

#ifndef LOCAL_MATCHER_HPP_
#define LOCAL_MATCHER_HPP_

#include <string>
#include <vector>
#include "common_defs.hpp"

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

enum class LocalMatchResultType
{
    ERROR=0, // error case 
    NONE,    // no match
    SINGLE,  // one match
    MULTIPLE  // more than one match
};

struct LocalMatchEntry
{
    vector<OkString>    human_command;
    vector<OkString>    real_command;
};

// This class contains the information by the current user at the interface, 
// which contains the following
// - a flag indicating the result type
// - what the user typed in
// - the matched human command, with arguments replaced
// - the matched real command of current platform, arguments replaced
// mutiple result entries are sorted according to relevance 
struct LocalMatchResult
{
    LocalMatchResultType     flag;
    string                   user_command;
    vector<LocalMatchEntry> match_results;
};

class LocalMatcher
{
public:
    LocalMatcher();
    
public:
    void match(const vector<string>& command, LocalMatchResult& result) const;
};

} // end of namespace detail
} // end of namespace okshell

#endif /* LOCAL_MATCHER_HPP_ */
