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

namespace okshell
{
namespace detail
{
using std::string;

// TODO, customized home directory
const string kConfigDir = "/home/ylzhang/.ok/";
const string kProfileLocal = kConfigDir + "profile";
const string kProfileCloudDemo = kConfigDir + "profile_cloud_demo";

} // end namespace detail
} // end namespace okshell


#endif /* GLOBALS_H_ */
