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
#include <set>

#include "common_defs.h"

namespace okshell
{
    
// return if a string follow the format <blah>
bool is_argument(const std::string& s);

// return if a string contains the format <blah>
bool contains_argument(const std::string& s);

// take a string as input, return the list of arguments in the string
// does not remove duplicate, i.e., result has multiple instances 
// of an argument if it appears multiple times in input string
void search_arguments(const std::string& input, 
        std::vector<std::string>& result);

// take a string as input, return the *set* of arguments in the string
// duplcates are eliminated
void search_arguments(const std::string& input, std::set<std::string>& result);

// make the OS label such as "  (Linux) $ "
std::string os_label(const std::string& os_name);

// given a prompt message, return the the message with header added
std::string prompt_with_header(const std::string& message);

} // end namespace okshell

#endif /* OKSHELL_UTILS_H_ */
