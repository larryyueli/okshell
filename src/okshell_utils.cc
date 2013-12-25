/*
 * okshell_utils.cc
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

void search_argument(const string& input, vector<string>& result)
{
//    bool bracket_open = false;
//    string buf{};
//    for (const char& c : input)
//    {
//        if (c == '<')
//        {
//            if 
//        }
//    }
}

} // end namespace detail
} // end namespace okshell
