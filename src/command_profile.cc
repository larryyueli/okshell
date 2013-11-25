/*
 * command_profile.cc
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#include "command_profile.h"
#include <fstream>

namespace okshell
{
namespace detail
{
using std::ifstream;

void CommandProfile::load_from_file(const string& filename)
{
    ifstream ifs(filename.c_str(), std::ios_base::binary | std::ios_base::in);
    boost::archive::binary_iarchive ia(ifs);
    ia >> entries_;
    return;
}

const vector<CommandProfileEntry>& CommandProfile::get_entries() const
{
    return entries_;
}


} // end namespace detail
} // end namespace okshell
