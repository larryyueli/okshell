/*
 * globals.h
 * Definitions of global variables
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <string>
#include <boost/regex.hpp>
#include "utils.h"

namespace okshell
{
namespace detail
{
using std::string;

const string kEXE = "ok";

const string kConfigDir = utils::get_home_dir() + "/.ok/";
const string kProfileLocal = kConfigDir + "profile";
//const string kProfileCloudDemo = kConfigDir + "profile_cloud_demo";
const string kConfigFile = kConfigDir + "config";

const string kPromptLearnCloud = "Learn from cloud? [Y/n]";
const string kPromptAddManually = "Add the command manually? [Y/n]";
const string kPrintOutExecuting = "Executing command...\n";

const string kOSHuman    = "Human";
const string kOSLinux    = "Linux";
const string kOSWindows  = "Windows";
const string kOSMac      = "Mac";

const boost::regex kArgRegEx {"<..*>"};

} // end namespace detail
} // end namespace okshell

#endif /* GLOBALS_H_ */
