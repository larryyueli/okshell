/*
 * utils.cpp
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#include "utils.hpp"
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

string boldface(const string& s)
{
    return "\033[1m" + s + "\033[0m";
}

} // end namespace detail
} // end namespace utils
