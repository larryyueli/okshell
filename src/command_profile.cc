/*
 * command_profile.cc
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

#include "command_profile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "globals.h"
#include "okshell_utils.h"
#include "logger.h"
#include "utils.h"

namespace okshell
{
using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::ostringstream;
using std::endl;
using std::setw;
using std::string;
using std::vector;

string CommandProfileEntry::str() const
{
    ostringstream oss;
    oss << setw(14) << os_label(kOSHuman);
    for (const auto& w : human_profile)
    {
        oss << w.impl << " ";
    }
    oss << "\n" << setw(14) << os_label(kOSLinux);
    for (const auto& w : real_profile)
    {
        oss << w.impl << " ";
    }
    return oss.str();
}

const vector<CommandProfileEntry>& CommandProfile::get_entries() const
{
    return entries_;
}

void CommandProfile::add_entry(const CommandProfileEntry& entry)
{
    entries_.push_back(entry);
}

void CommandProfile::remove_entry(size_t pos)
{
    if (pos >= entries_.size())
    {
        throw OkShellException(
                "CommandProfile::remove_entry, pos out of range");
    }
    entries_.erase(entries_.begin() + pos);
    return;
}

bool CommandProfile::empty() const
{
    return entries_.empty();
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

string CommandProfile::str() const
{
    ostringstream oss;
    for (const auto& entry : entries_)
    {
        oss << entry.str() << "\n\n";
    }
    return oss.str();
}

void CommandProfile::display() const
{
    if (empty())
    {
        mycerr << "Profile is empty." << endl;
    }
    else
    {
        mycerr << "Below is the list of the commands in your profile:" << endl;
        for (const auto& entry : entries_)
        {
            mycerr << "\n";
            mycerr << setw(14) << os_label(kOSHuman) 
                   << utils::vec_str(vec_color(entry.human_profile)) << "\n";
            mycerr << setw(14) << os_label(kOSLinux) 
                   << utils::vec_str(vec_color(entry.real_profile)) << "\n";
        }
        return;
    }
}

} // end namespace okshell
