/*
 * command_profile.h
 * The definition of the entries stored in the command profile
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

#ifndef COMMAND_PROFILE_H_
#define COMMAND_PROFILE_H_

#include "common_defs.h"

namespace okshell
{
// TODO, store entries for different OS
struct CommandProfileEntry
{
    vector<OkString>    human_profile;
    vector<OkString>    real_profile;
    
public:
    // return string representation
    string str() const;
    
private:
    // define serialization rules
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & human_profile;
        ar & real_profile;
    }
};

class CommandProfile
{
public:
    CommandProfile () {}
    
private:
    // Here we use a vector instead of a map because we want to support
    // that one human command being mapped to multiple real commands. 
    // User may sometimes in need of this type of mapping, therefore
    // it is the user's responsiblity to keep the mapping single by 
    // creating command more carefully or by deleting commands.
    vector<CommandProfileEntry>   entries_;
    
public:
    // accessor for entries
    const vector<CommandProfileEntry>& get_entries() const;
    
    // add an entry to the profile
    void add_entry(const CommandProfileEntry& entry);
    
    // remove from the profile the entry at position pos
    // throw OkShellException if pos is out of range
    void remove_entry(size_t pos);
    
    // return whether entries_ is an empty vector
    bool empty() const;
        
    // read the profile file on disk and load it into entries_
    void load_from_file(const string& filename);
    
    // write entries_ into file on disk
    // overwrite if file already exists
    void write_to_file(const string& filename) const;
    
    // return string representation of the profile
    string str() const;
    
    // display the whole profile in readable format
    void display() const;
    
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & entries_;
    }
};

} // end namespace okshell

#endif /* COMMAND_PROFILE_H_ */
