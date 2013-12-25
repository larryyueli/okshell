/*
 * utils.h
 * utilities and helpers that are independent of okshell
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

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>
#include <boost/regex.hpp>

namespace utils
{
namespace detail
{
using std::string;
using std::vector;

// convert a string to lower case and return it.
string lowercase(const string& s);

// return the string representation of a vector of Ts
template <typename T>
string vec_str(const vector<T>& v);

// return the ANSI escaped code of boldface string
string boldface(const string& s);

// run a system command, return the return value of the command
int exe_system(const string& command);

// return if a string contains a substring that matches regex
bool contains_regex(const string& s, const string& re_str);
bool contains_regex(const string& s, const boost::regex& re);

// get the path of home folder of current user
string get_home_dir();

// generate a uuid in string format
string generate_uuid();


} // end namespace detail

using detail::lowercase;
using detail::vec_str;
using detail::boldface;
using detail::exe_system;
using detail::contains_regex;
using detail::get_home_dir;
using detail::generate_uuid;

} // end namespace utils

#endif /* UTILS_H_ */
