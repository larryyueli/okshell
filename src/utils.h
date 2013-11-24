/*
 * utils.h
 * utilities and helpers
 * 
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>

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

// Display a prompt message and ask for user's keyboard input
// The input is casted into type T
// If input is invaid, keep asking until valid
// Empty input is valid, and returns default value
template <typename T>
T keyboard_input(const string& prompt_message, const T& default_value);

} // end namespace detail

using detail::lowercase;
using detail::vec_str;
using detail::boldface;
using detail::exe_system;

} // end namespace utils

#endif /* UTILS_H_ */