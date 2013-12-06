/*
 * initializer.h
 * class used for initializing OkShell, 
 * including creating initial empty profile and config files
 *
 *  Created on: 2013-12-04
 *      Author: Larry Yueli Zhang
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
};

} // end namespace detail
using detail::Initializer;
} // end namespace okshell

#endif /* INITIALIZER_H_ */
