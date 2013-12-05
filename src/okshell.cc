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
    if (mode == MainMode::HELP || mode == MainMode::EMPTY)
    {
        HelpDisplayer help_displayer{};
        help_displayer.display();
    }
    else if (mode == MainMode::NORMAL)
    {
        NormalCommander commander{config_};
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
        if (config_.interactive_on())
        {
            cerr << endl;
        }
    }
    else if (mode == MainMode::CONFIG)
    {
        ConfigCommander commander{config_};
        commander.process(remaining_args);
        cerr << endl;
    }
    else
    {
        throw std::runtime_error("OkShell::run, invalide mode_t");
    }
    return rv;
}

} // end namespace detail
} // end namespace okshell

