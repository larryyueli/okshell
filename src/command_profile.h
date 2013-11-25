/*
 * command_profile.h
 * The definition of the entries stored in the command profile
 *
 *  Created on: 2013-11-24
 *      Author: Larry Yueli Zhang
 */

#ifndef COMMAND_PROFILE_H_
#define COMMAND_PROFILE_H_

#include "common_defs.h"

namespace okshell
{
namespace detail
{
    
struct CommandProfileEntry
{
    vector<OkString>    human_command;
    vector<OkString>    real_command;
    
private:
    // define serialization rules
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & human_command;
        ar & real_command;
    }
};

class CommandProfile
{
public:
    CommandProfile () {}
    
private:
    vector<CommandProfileEntry>   entries_;
    
public:
    // accessor for entries
    const vector<CommandProfileEntry>& get_entries() const;
    
    // add an entry to the profile
    void add_entry(const CommandProfileEntry& entry);
    
    // read the profile file on disk and load it into entries_
    void load_from_file(const string& filename);
    
    // write entries_ into file on disk
    // overwrite if file already exists
    void write_to_file(const string& filename) const;
    
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & entries_;
    }
};
} // end namespace detail
} // end namespace okshell

#endif /* COMMAND_PROFILE_H_ */
