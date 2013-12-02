/*
 * config_help_displayer.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "config_help_displayer.h"
#include <iostream>
#include "utils.h"

namespace okshell
{
namespace detail
{
using std::cout;
using std::cerr;
using std::endl;
using utils::boldface;

void ConfigHelpDisplayer::display() const
{
    cout << "\n========================= " << boldface("OkShell Config Guide") << " =========================\n\n  ";
    cout << "To perform a configuration task, type `ok ok` followed by one of the\n  ";
    cout << "following options. For example,\n\n  ";
    cout << "    " << boldface("$ ok ok interactive off") << "\n\n  ";
    cout << "OPTIONS:\n\n  ";
    cout << "    " << boldface("interactive on/off") << "\n  ";
    cout << "        When turned off, messages starting with [OKSHELL] do not show\n  ";
    cout << "        up. The command is executed only when having a confident match.\n\n  ";
    cout << "    " << boldface("cloud on/off") << "\n  ";
    cout << "        Turn on/off connection to cloud.\n\n  ";
    cout << "    " << boldface("sync") << "\n  ";
    cout << "        Synchronize local pofile with cloud.\n\n  ";
    cout << "    " << boldface("restore") << "\n  ";
    cout << "        Restore local profile from cloud with user ID.\n\n  ";
    cout << "    " << boldface("userid") << "\n  ";
    cout << "        Display the OkShell user ID.\n\n  ";
    cout << "    " << boldface("edit") << "\n  ";
    cout << "        Edit or remove commands in profile.\n\n  ";
//    cout << "    " << boldface("display profile/config") << "\n  ";
//    cout << "        Print out profile/config in readable format.\n\n  ";
//    cout << "    " << boldface("reinstall") << "\n  ";
//    cout << "        Start like a new OkShell user, with empty profile and newly\n  ";
//    cout << "        assigned user ID.\n\n";
    cout << "=============================== " << boldface("THE END") << " ================================\n  ";
    cout << endl;
}

    
} // end namespace detail
} // end namespace okshell

