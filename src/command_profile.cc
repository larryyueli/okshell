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
using std::ofstream;
using std::ios_base;

const vector<CommandProfileEntry>& CommandProfile::get_entries() const
{
    return entries_;
}

void CommandProfile::add_entry(const CommandProfileEntry& entry)
{
    entries_.push_back(entry);
}

void CommandProfile::load_from_file(const string& filename)
{
    ifstream ifs(filename.c_str(), ios_base::binary | ios_base::in);
    boost::archive::binary_iarchive ia(ifs);
    ia >> entries_;
    return;
}

void CommandProfile::write_to_file(const string& filename) const
{
    ofstream ofs(filename.c_str(), ios_base::binary | ios_base::out);
    boost::archive::binary_oarchive oa(ofs);
    oa << entries_;
}

} // end namespace detail
} // end namespace okshell
