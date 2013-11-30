/*
 * common_defs.cc
 *
 *  Created on: 2013-11-20
 *      Author: Larry Yueli Zhang
 */

#include "common_defs.h"
#include "utils.h"
#include "globals.h"

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

} // end namespace detail
} // end namespace okshell


