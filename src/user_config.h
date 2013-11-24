/*
 * user_config.h
 * The class that stores and accesses users's configuration settings
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#ifndef USER_CONFIG_H_
#define USER_CONFIG_H_

#include "common_defs.h"

namespace okshell
{
namespace detail
{
class UserConfig
{
public:
    UserConfig() {}
    
public:
    bool cloud_enabled() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(UserConfig);
};

} // end namespace detail
} // end namespace okshell

#endif /* USER_CONFIG_H_ */
