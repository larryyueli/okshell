/*
 * initializer.cc
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

#include "initializer.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include "globals.h"
#include "command_profile.h"
#include "config.h"
#include "logger.h"
#include "utils.h"
#include "keyboard_input.h"

namespace okshell
{
using std::cerr;
using std::endl;
using std::string;
using utils::boldface;

bool Initializer::uninitialized() const
{
    bool profile_exists = boost::filesystem::exists(kProfileLocal);
    bool config_exists = boost::filesystem::exists(kConfigFile);
    if (profile_exists && config_exists)
    {
        return false;
    }
    else if (!profile_exists && !config_exists)
    {
        return true;
    }
    throw OkShellException(
            "Initializer::uninitialized: only one is missing, not possible.");
    return false;
}

void Initializer::init() const
{
    create_folder_if_necessary();
    init_config();
    init_profile(); 
    return;
}

void Initializer::welcome() const
{
    Config config(kConfigFile);
    config.set_uuid(utils::generate_uuid());
    cerr << endl;
    mycerr << "You are using OkShell for the first time on this computer." 
           << endl;
    mycerr << "Below are some things you need to know." << endl;
    mycerr << "\n";
    mycerr << "OkShell's " << boldface("cloud feature") 
           << " (not active in current version)" << endl; 
    mycerr << "allows you to backup you profile in the cloud, as well as\n";
    mycerr << "to learn commands from other people using OkShell." << endl;
    mycerr << "\n";
    string use_cloud = yes_no_input(
            "Enable cloud feature? You can turn it off later. [Y/n]", "y");
    if (use_cloud == "y")
    {
        config.set_cloud_on();
        mycerr << "Cloud ON" << endl;
    }
    else
    {
        config.set_cloud_off();
        mycerr << "Cloud OFF" << endl;
    }
    mycerr << "\n";
    mycerr << "You are ready to go! Below is your unique OkShell user ID,\n";
    mycerr << "you can use it to restore you profile on other computers.\n";
    mycerr << "\n";
    mycerr << "   " << config.get_uuid() << endl;
    mycerr << "\n";
    mycerr << "What's next: Type `" << boldface("ok help") 
           << "` to see how to use OkShell." << endl;
    cerr << endl;
}

void Initializer::init_config() const
{
    ConfigFile config{};
    config.write_to_disk(kConfigFile);
    return;
}

void Initializer::init_profile() const
{
    CommandProfile profile;
    profile.write_to_file(kProfileLocal);
    return;
}

void Initializer::create_folder_if_necessary() const
{
    boost::filesystem::path folder(kConfigDir);
    if (!boost::filesystem::exists(folder) 
        || !boost::filesystem::is_directory(folder))
    {
        if (!boost::filesystem::create_directory(folder))
        {
            throw OkShellException(
                    "Failed to create config directory: " + kConfigDir);
        }
    }
    return;
}
    
} // end namespace okshell
