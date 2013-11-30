/*
 * okshell_utils.h
 * utility and helpers that are inside okshell namespace
 *
 *  Created on: 2013-11-29
 *      Author: Larry Yueli Zhang
 */

#ifndef OKSHELL_UTILS_H_
#define OKSHELL_UTILS_H_

#include <string>
#include <vector>

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;
    
// return if a string follow the format <blah>
bool is_argument(const string& s);

// return if a string contains the format <blah>
// if true, result is the matched part
// assuming there is only one match
// TODO, support mutiple match
bool search_argument(const string& s, string& result);

bool contains_argument(const string& s);

// make the OS label such as "  (Linux) $ "
string os_label(const string& os_name);

} // end namespace detail
} // end namespace okshell

#endif /* OKSHELL_UTILS_H_ */
