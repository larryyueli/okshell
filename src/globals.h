/*
 * globals.h
 * Definitions of global variables
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

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <string>
#include <boost/regex.hpp>
#include "utils.h"

namespace okshell
{
using std::string;

const string kEXE = "ok";

const string kConfigDir = utils::get_home_dir() + "/.ok/";
const string kProfileLocal = kConfigDir + "profile";
const string kConfigFile = kConfigDir + "config";

const string kPromptLearnCloud = "Learn from cloud? [Y/n]";
const string kPromptAddManually = "Add the command manually? [Y/n]";
const string kPrintOutExecuting = "Executing command...\n";
const string kPromotWouldLearnFromCloud = 
        "(Would learn from cloud once it is implemented.)";

const string kOSHuman    = "Human";
const string kOSLinux    = "Linux";
const string kOSWindows  = "Windows";
const string kOSMac      = "Mac";

const boost::regex kArgRegEx {"<..*>"};

} // end namespace okshell

#endif /* GLOBALS_H_ */
