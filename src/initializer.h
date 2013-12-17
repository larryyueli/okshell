/*
 * initializer.h
 * class used for initializing OkShell, 
 * including creating initial empty profile and config files
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

#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include "common_defs.h"
#include "globals.h"

namespace okshell
{
namespace detail
{
class Initializer
{
public:
    Initializer() {}
    
public:
    // check whether OkShell is unintialized
    bool uninitialized() const;
    
    // perform the intialization
    void init() const;
    
    // Display welcome messages
    void welcome() const;
    
private:
    void init_config() const;
    void init_profile() const;
    void create_folder_if_necessary() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(Initializer);
};

} // end namespace detail
using detail::Initializer;
} // end namespace okshell

#endif /* INITIALIZER_H_ */
