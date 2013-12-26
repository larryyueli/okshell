/*
 * common_defs.cc
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

#include "common_defs.h"
#include "utils.h"
#include "globals.h"

namespace okshell
{
using std::string;
using std::vector;
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

} // end namespace okshell

