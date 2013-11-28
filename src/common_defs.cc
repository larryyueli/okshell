/*
 * common_defs.cc
 *
 *  Created on: 2013-11-20
 *      Author: Larry Yueli Zhang
 */

#include "common_defs.h"
#include <sstream>
#include <iomanip>
#include "utils.h"

namespace okshell
{
namespace detail
{
using utils::boldface;

string OkString::str_color() const
{
    if (flag == OkStringType::ARG)
        return boldface(impl);
    else
        return impl;
}

string OkString::str_plain() const
{
    return impl;
}

vector<string> vec_color(const vector<OkString>& v)
{
    vector<string> result{};
    for (auto& s : v)
        result.push_back(s.str_color());
    return result;
}

vector<string> vec_plain(const vector<OkString>& v)
{
    vector<string> result{};
    for (auto& s : v)
        result.push_back(s.str_plain());
    return result;    
}

bool is_argument(const string& s)
{
    return (s.size() > 2 && s.front() == '<' && s.back() == '>');
}

string os_label(const string& os_name)
{
    string with_brackets = "(" + os_name + ") $ ";
    std::ostringstream oss;
    oss << std::setw(10) << with_brackets;
    return oss.str();
}

} // end namespace detail
} // end namespace okshell


