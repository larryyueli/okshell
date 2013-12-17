/*
 * okshell_utils.h
 * utility and helpers that are inside okshell namespace
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
