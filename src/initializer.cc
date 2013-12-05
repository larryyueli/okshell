/*
 * initializer.cc
 *
 *  Created on: 2013-12-04
 *      Author: Larry Yueli Zhang
 */

#include "initializer.h"
#include <stdexcept>
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
namespace detail
{
using std::cerr;
using std::endl;
using utils::boldface;

bool Initializer::uninitialized() const
{
    std::cout << "Inside unintialized" << std::endl;
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
    throw std::runtime_error(
            "Initializer::uninitialized: only one is missing, not possible.");
    return false;
}

void Initializer::init() const
{
    init_config();
    init_profile();
    return;
}

// TODO, uuid generator
void Initializer::welcome() const
{
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
    if (use_cloud == "y" || use_cloud == "n")
    {
        // TODO, perform actual configuration
        mycerr << "Cloud ON" << endl;
    }
    mycerr << "\n";
    mycerr << "You are ready to go! Below is your unique OkShell user ID,\n";
    mycerr << "you can use it to restore you profile on other computers.\n";
    mycerr << "\n";
    mycerr << "   550e8400-e29b-41d4-a716-446655440000" << endl;
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
    
} // end namespace detail
} // end namespace okshell
