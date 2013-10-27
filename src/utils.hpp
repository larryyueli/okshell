/*
 * utils.hpp
 * utilities and helpers
 * 
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <vector>

namespace okshell
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

} // end namespace detail
} // end namespace okshell

#endif /* UTILS_HPP_ */
