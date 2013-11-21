/*
 * globals.hpp
 * Definitions of global variables
 *
 *  Created on: 2013-10-27
 *      Author: ylzhang
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

#include <string>

namespace okshell
{
namespace detail
{
using std::string;

const string kConfigDir = "~/.ok/";
const string kProfileMain = kConfigDir + "profile_main";
const string kProfileCloudDemo = kConfigDir + "profile_cloud_demo";

} // end namespace detail
} // end namespace okshell


#endif /* GLOBALS_HPP_ */
