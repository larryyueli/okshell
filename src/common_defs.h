/*
 * common_defs.h
 * Common definitions of that are used everywhere in the project
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

#ifndef COMMON_DEFS_H_
#define COMMON_DEFS_H_

#include <string>
#include <vector>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

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
    OkString () 
        : flag(OkStringType::CMD) {}
    OkString(OkStringType flag, const string& impl)
        : flag(flag), impl(impl) {}
    
    OkStringType    flag;
    string          impl;

    // return the string representation with ANSI color code
    // arguments are in boldface    
    string str_color() const;
    
    // return the string representation without color code
    // arguments are in boldface
    string str_plain() const;
    
private:
    // define serialization rules
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & flag;
        ar & impl;
    }
};

// convert a vector of okstring to vector string, with color code
// arguments are in boldface
vector<string> vec_color(const vector<OkString>& v);

// convert a vector of okstring to vector string, without color code
// arguments are in boldface
vector<string> vec_plain(const vector<OkString>& v);

// Entry class of an argment in a command stored in profile
// TODO, possible enhancement, allow duplidate entries of an arg
struct ArgEntry
{
    ArgEntry () 
        : name(), index_human(0), index_real(0) {}
    
    string      name;           // e.g., "<arg1>"
    size_t      index_human;    // position in human command
    size_t      index_real;     // position in real command
};

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);               \
    void operator=(const TypeName&)

} // end namespace detail
} // end namespace okshell

#endif /* COMMON_DEFS_H_ */
