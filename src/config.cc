/*
 * config.cc
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

#include "config.h"
#include <utility>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "logger.h"

namespace okshell
{
using std::make_pair;
using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::endl;
using std::setw;
using std::string;

bool ConfigFile::get_value(const string& key, string& value) const
{
    const auto& iter = impl_.find(key);
    if (iter == impl_.end())
    {
        value = "";
        return false;
    }
    value = iter->second;
    return true;
}

void ConfigFile::add_update_key_value(const string& key, const string& value)
{
    impl_[key] = value;
    return;
}

void ConfigFile::load_from_disk(const string& filename)
{
    ifstream ifs(filename.c_str(), ios_base::binary | ios_base::in);
    boost::archive::binary_iarchive ia(ifs);
    ia >> impl_;
    return;
}

void ConfigFile::write_to_disk(const string& filename) const
{
    ofstream ofs(filename.c_str(), ios_base::binary | ios_base::out);
    boost::archive::binary_oarchive oa(ofs);
    oa << impl_;
}

void ConfigFile::display() const
{
    mycerr << "Below is the list of your configuration entries:\n";
    mycerr << "\n";
    for (auto& p : impl_)
    {
        mycerr << "    " << setw(16) << std::left << p.first << p.second << "\n";
    }
}

Config::Config(const string& config_filename)
    : filename_(config_filename)
{
    load_from_disk();
}

bool Config::interactive_on() const
{
    string value;
    if (file_.get_value("interactive", value))
    {
        return value == "on";
    }
    // default value is true
    return true;
}

void Config::set_interactive_on()
{
    file_.add_update_key_value("interactive", "on");
    write_to_disk();
    return;
}

void Config::set_interactive_off()
{
    file_.add_update_key_value("interactive", "off");
    write_to_disk();
    return;
}

bool Config::cloud_on() const
{
    string value;
    if (file_.get_value("cloud", value))
    {
        return value == "on";
    }
    // default value is true
    return true;
}

void Config::set_cloud_on()
{
    file_.add_update_key_value("cloud", "on");
    write_to_disk();
    return;
}

void Config::set_cloud_off()
{
    file_.add_update_key_value("cloud", "off");
    write_to_disk();
    return;
}

string Config::get_uuid() const
{
    string value;
    if (file_.get_value("uuid", value))
    {
        return value;
    }
    throw OkShellException("UUID does not exist!");
    return "";
}

void Config::set_uuid(const string& uuid)
{
    file_.add_update_key_value("uuid", uuid);
    write_to_disk();
    return;
}

void Config::load_from_disk()
{
    file_.load_from_disk(filename_);
}

void Config::write_to_disk() const
{
    file_.write_to_disk(filename_);
}

void Config::display() const
{
    file_.display();
}

} // end namespace okshell

