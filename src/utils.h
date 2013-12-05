/*
 * utils.h
 * utilities and helpers that are independent of okshell
 * 
 *  Created on: 2013-10-27
 *      Author: Larry Yueli Zhang
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
// if true, result is the matched part
// assuming there is only one match
// TODO, support mutiple match
bool search_regex(const string& s, const string& re_str, string& result);
bool search_regex(const string& s, const boost::regex& re, string& result);


// return if a string contains a substring that matches regex
bool contains_regex(const string& s, const string& re_str);
bool contains_regex(const string& s, const boost::regex& re);

// get the path of home folder of current user
string get_home_dir();


} // end namespace detail

using detail::lowercase;
using detail::vec_str;
using detail::boldface;
using detail::exe_system;
using detail::search_regex;
using detail::contains_regex;
using detail::get_home_dir;

} // end namespace utils

#endif /* UTILS_H_ */
