/*
 * help_displayer.h
 * The class for displaying the main help.
 * For displaying help in config mode, see config_help_displayer.hpp
 *
 *  Created on: 2013-11-15
 *      Author: Larry Yueli Zhang
 */

#ifndef HELP_DISPLAYER_H_
#define HELP_DISPLAYER_H_

namespace okshell
{
namespace detail
{
class HelpDisplayer
{
public:
    HelpDisplayer() {}
    
public:
    void display() const;
};
    
} // end namespace detail
} // end namespace okshell


#endif /* HELP_DISPLAYER_H_ */
