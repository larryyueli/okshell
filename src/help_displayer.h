/*
 * help_displayer.h
 * The class for displaying the main help.
 * For displaying help in config mode, see config_help_displayer.hpp
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

#ifndef HELP_DISPLAYER_H_
#define HELP_DISPLAYER_H_

#include "common_defs.h"

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
    
private:
    DISALLOW_COPY_AND_ASSIGN(HelpDisplayer);
};
    
} // end namespace detail
} // end namespace okshell


#endif /* HELP_DISPLAYER_H_ */
