/*
 * user_config.cc
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#include "user_config.h"

namespace okshell
{
namespace detail
{
    
bool UserConfig::cloud_enabled() const
{
    // TODO, load config file and check the flag for cloud setting
    return true;
}
    
} // end namespace detail
} // end namespace okshell
