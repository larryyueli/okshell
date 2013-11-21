/*
 * common_defs.hpp
 * Common definitions of that are used everywhere in the project
 *
 *  Created on: 2013-11-20
 *      Author: Larry Yueli Zhang
 */

#ifndef COMMON_DEFS_HPP_
#define COMMON_DEFS_HPP_

#include <string>
#include <vector>

namespace okshell
{
namespace detail
{
using std::string;
using std::vector;

// a flag indicating whether a string is part of the command or argument
enum class OkStringType
{
    CMD = 0, ARG
};

struct OkString
{
    OkStringType    flag;
    string          impl;

    // return the string representation with ANSI color code
    // arguments are in boldface    
    string str_color() const;
    
    // return the string representation without color code
    // arguments are in boldface
    string str_plain() const;
};

// convert a vector of okstring to vector string, with color code
// arguments are in boldface
vector<string> vec_color(const vector<OkString>& v);

// convert a vector of okstring to vector string, without color code
// arguments are in boldface
vector<string> vec_plain(const vector<OkString>& v);

} // end namespace detail
} // end namespace okshell

#endif /* COMMON_DEFS_HPP_ */
