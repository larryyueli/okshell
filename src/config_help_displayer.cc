/*
 * config_help_displayer.cc
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#include "config_help_displayer.h"
#include <iostream>

namespace okshell
{
namespace detail
{
using std::cout;
using std::cerr;
using std::endl;

void ConfigHelpDisplayer::display() const
{
    cout << "ConfigHelpdisplayer::display" << endl;
}

    
} // end namespace detail
} // end namespace okshell

