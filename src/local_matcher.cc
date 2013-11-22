/*
 * local_matcher.cc
 *
 *  Created on: 2013-11-20
 *      Author: Larry Yueli Zhang
 */

#include "local_matcher.h"
#include <sstream>
#include <iomanip>
#include <ostream>
#include "utils.h"

namespace okshell
{
namespace detail
{
using std::ostringstream;
using std::setw;
using std::endl;
using utils::vec_str;

string LocalMatchEntry::color_str_human() const
{
    return vec_str(vec_color(human_command));
}

string LocalMatchEntry::color_str_real() const
{
    return vec_str(vec_color(real_command));
}

string LocalMatchEntry::plain_str_human() const
{
    return vec_str(vec_plain(human_command));
}

string LocalMatchEntry::plain_str_real() const
{
    return vec_str(vec_plain(real_command));
}

string LocalMatchResult::repr_multiple() const
{
    ostringstream oss;
    for (size_t i = 0; i < match_results.size(); ++i)
    {
        int seq = i + 1;
        const auto& entry = match_results[i];
        oss << setw(3) << seq << ". " << entry.color_str_human() << "\n"
            << setw(5) << " " << "REAL: " << entry.color_str_real() << "\n\n";
    }
    return oss.str();
}

LocalMatcher::LocalMatcher(const string& profile_filename)
{
    
}

void LocalMatcher::match(const vector<string>& command, 
        LocalMatchResult& result) const
{
    
}

} // end namespace detail
} // end namespace okshell


