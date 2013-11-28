/*
 * okshell.cpp
 *
 *  Created on: 2013-10-25
 *      Author: Larry Yueli Zhang
 */

#include "okshell.h"
#include <stdexcept>
#include <iostream>
#include "mode_parser.h"
#include "help_displayer.h"
#include "normal_commander.h"
#include "config_commander.h"
#include "logger.h"
#include "keyboard_input.h"
#include "utils.h"
#include "logger.h"

namespace okshell
{
namespace detail
{
using std::cerr;
using std::endl;
using utils::boldface;

// For the meaning of return values from process functions,
// see the comment for NormalCommander::process in normal_commander.h
int OkShell::run(const vector<string>& args) // args could be empty vector
{
    int rv = 0;
    vector<string> remaining_args{};
    ModeParser mode_parser{};
    MainMode mode = mode_parser.parse(args, remaining_args);
    if (mode == MainMode::HELP)
    {
        HelpDisplayer help_displayer{};
        help_displayer.display();
    }
    else if (mode == MainMode::NORMAL)
    {
        NormalCommander commander{};
        rv = commander.process(remaining_args);
        if (rv == 2)
        {
            mycerr << "\n";
            mycerr << "Did not execute a command." << endl;
            rv = 0;
        }
        else if (rv == 3)
        {
            mycerr << "\n";
            mycerr << "Learned something new, try running the command again."
                   << endl;
            rv = 0;
        }
    }
    else if (mode == MainMode::CONFIG)
    {
        ConfigCommander commander{};
        commander.process(remaining_args);
    }
    else if (mode == MainMode::EMPTY)
    {
        welcome(); // TODO, Only for demo
    }
    else
    {
        throw std::runtime_error("OkShell::run, invalide mode_t");
    }
    cerr << endl;
    return rv;
}

void OkShell::welcome() const
{
    cerr << endl;
    mycerr << "You are using OkShell for the first time on this computer." 
           << endl;
    mycerr << "Below are some things you need to know." << endl;
    mycerr << "\n";
    mycerr << "OkShell's " << boldface("cloud feature") 
           << " allows you to backup you profile in\n"; 
    mycerr << "the cloud, as well as to learn commands from other people\n";
    mycerr << "using OkShell." << endl;
    mycerr << "\n";
    YesNoInputValidator yn_validator;
    string use_cloud = keyboard_input<string>(
            "Enable cloud feature? You can turn it off later. [Y/n]", 
            true, "y", &yn_validator);
    if (use_cloud == "y" || use_cloud == "n")
    {
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
}

} // end namespace detail
} // end namespace okshell

