/*
 * initializer.cc
 *
 *  Created on: 2013-12-04
 *      Author: Larry Yueli Zhang
 */

#include "initializer.h"

namespace okshell
{
namespace detail
{
bool Initializer::uninitialized() const
{
    return false;
}

void Initializer::init() const
{
    
}
    
} // end namespace detail
} // end namespace okshell
