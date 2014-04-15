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
const std::string kEXE = "ok";
const std::string kPromptHeader = "  [OKSHELL]  ";

const std::string kConfigDir = utils::get_home_dir() + "/.ok/";
const std::string kProfileLocal = kConfigDir + "profile";
const std::string kConfigFile = kConfigDir + "config";

const std::string kPromptLearnCloud = "Learn from cloud? [Y/n]";
const std::string kPromptAddManually = "Add the command manually? [Y/n]";
const std::string kPrintOutExecuting = "Executing command...\n";
const std::string kPromotWouldLearnFromCloud = 
        "(Would learn from cloud once the cloud feature is activated.)";

const std::string kOSHuman    = "Human";
const std::string kOSLinux    = "Linux";
const std::string kOSWindows  = "Windows";
const std::string kOSMac      = "Mac";

#if defined(__linux)
const std::string kCurrentOS = kOSLinux;
#elif defined(__APPLE__)
#error "OkShell is not available for Apple yet."
#elif defined(__WIN32__)
#error "OkShell is not available for Windows yet."
#else
#error "OkShell is not available for you operating system yet."
#endif

const boost::regex kArgRegEx {"<..*>"};

const std::string kCloudIP = "localhost";
const std::string kCloudPort = "5678";

} // end namespace okshell

#endif /* GLOBALS_H_ */
