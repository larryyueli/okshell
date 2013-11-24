/*
 * utils.cpp
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#include "utils.h"
#include <sstream>
#include <boost/algorithm/string.hpp>

namespace utils
{
namespace detail
{

string lowercase(const string& s)
{
    string s2 = s;
    boost::to_lower(s2);
    return s2;
}

template <typename T>
string vec_str(const vector<T>& v)
{
    std::ostringstream oss;
    for (auto& s : v)
    {
        oss << s;
        oss << " ";
    }
    return oss.str();
}

// instantiation of the template function
template string vec_str<string>(const vector<string>& v);


string boldface(const string& s)
{
    return "\033[1m" + s + "\033[0m";
}

int exe_system(const string& command)
{
    return system(command.c_str());
}

} // end namespace detail
} // end namespace utils
