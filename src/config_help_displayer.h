/*
 * config_help_displayer.h
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#ifndef CONFIG_HELP_DISPLAYER_H_
#define CONFIG_HELP_DISPLAYER_H_

#include "common_defs.h"

namespace okshell
{
namespace detail
{
class ConfigHelpDisplayer
{
public:
    ConfigHelpDisplayer() {}
    
public:
    void display() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(ConfigHelpDisplayer);
};
    
} // end namespace detail
} // end namespace okshell

#endif /* CONFIG_HELP_DISPLAYER_H_ */
