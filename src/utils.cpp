/*
 * utils.cpp
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#include "utils.hpp"
#include <sstream>
#include <boost/algorithm/string.hpp>

namespace okshell
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
} // end namespace detail
} // end namespace okshell
