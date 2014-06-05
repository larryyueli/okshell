/*
 * connection_manager.h
 * The manager class that owns and manages all live connections
 *
 * Copyright (C) 2014  Larry Yueli Zhang
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

#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include <set>

#include "common_defs.h"
#include "connection.h"

namespace okshell
{
// Manages open connections so that they may be cleanly stopped when 
// the server needs to shut down.
class ConnectionManager
{
public:
    // Constructor
    ConnectionManager();
    
private:
    // The set of the managed connections
    std::set<Connection::Pointer>       connections_;
    
public:
    // Add the speciefied connection to the manager and start it
    void start(Connection::Pointer pconn);
    // Stop the specified connection
    void stop(Connection::Pointer pconn);
    // Stop all connections
    void stop_all();
    
public:
    DISALLOW_COPY_AND_ASSIGN(ConnectionManager)
};
} // end namespace okshell

#endif /* CONNECTION_MANAGER_H_ */
