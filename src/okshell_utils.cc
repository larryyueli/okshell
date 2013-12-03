/*
 * okshell_utils.cc
 *
 *  Created on: 2013-11-29
 *      Author: Larry Yueli Zhang
 */

#include "okshell_utils.h"
#include <sstream>
#include <iomanip>
#include <boost/regex.h>
#include "globals.h"
#include "utils.h"

namespace okshell
{
namespace detail
{
using std::setw;

bool is_argument(const string& s)
{
    return (s.size() > 2 && s.front() == '<' && s.back() == '>');
}

bool search_argument(const string& s, string& result)
{
    return utils::search_regex(s, kArgRegEx, result);
}

bool contains_argument(const string& s)
{
    return utils::contains_regex(s, kArgRegEx);
}

string os_label(const string& os_name)
{
    string with_brackets = "(" + os_name + ") $ ";
    std::ostringstream oss;
    oss << setw(10) << with_brackets;
    return oss.str();
}

} // end namespace detail
} // end namespace okshell
