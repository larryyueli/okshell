/*
 * cloud_sync.h
 * The class used for syncing with cloud.
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

#ifndef CLOUD_SYNC_H_
#define CLOUD_SYNC_H_

#include "common_defs.h"

namespace okshell
{

class CloudSync
{
public:
    CloudSync() {}
    
public:
    // sync with cloud
    // return whether sync was successful
    bool sync() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(CloudSync);
};

} // end namespade okshell

#endif /* CLOUD_SYNC_H_ */
