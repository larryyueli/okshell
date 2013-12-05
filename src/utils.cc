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

bool search_regex(const string& s, const string& re_str, string& result)
{
    boost::regex re{re_str};
    boost::match_results<std::string::const_iterator> m;
    if (boost::regex_search(s, m, re))
    {
        result = m[0].str();
        return true;
    }
    return false;
}

bool search_regex(const string& s, const boost::regex& re, string& result)
{
    boost::match_results<std::string::const_iterator> m;
    if (boost::regex_search(s, m, re))
    {
        result = m[0].str();
        return true;
    }
    return false;
}

bool contains_regex(const string& s, const string& re_str)
{
    boost::regex re{re_str};
    boost::match_results<std::string::const_iterator> m;
    return boost::regex_search(s, m, re);
}

bool contains_regex(const string& s, const boost::regex& re)
{
    boost::match_results<std::string::const_iterator> m;
    return boost::regex_search(s, m, re);
}

string get_home_dir()
{
    return string{getenv("HOME")};
}

} // end namespace detail
} // end namespace utils
