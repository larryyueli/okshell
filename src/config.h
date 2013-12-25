/*
 * config.h
 * The class that stores the configurations
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

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <map>
#include "common_defs.h"
#include "globals.h"

namespace okshell
{
namespace detail
{
using std::string;

// impl is map from key to value
class ConfigFile
{
public:
    ConfigFile () {}
    
private:
    std::map<string, string>     impl_;

public:
    // return whether the key exists
    bool get_value(const string& key, string& value) const;
    
    // add the key value if key does not exists
    // overwrite the value if key already exists
    void add_update_key_value(const string& key, const string& value);
    
    void load_from_disk(const string& filename);
    void write_to_disk(const string& filename) const;
    
    // Display the config entries in readable format
    void display() const;
        
private:
    DISALLOW_COPY_AND_ASSIGN(ConfigFile);
};

class Config
{
public:
    Config(const string& config_filename);
    
private:
    string                  filename_;
    ConfigFile              file_;
    
public:
    // default value true
    bool interactive_on() const;
    void set_interactive_on();
    void set_interactive_off();
    
    // default value true
    bool cloud_on() const;
    void set_cloud_on();
    void set_cloud_off();
    
    string get_uuid() const;
    void set_uuid(const string& uuid);
    
    // Display the config entries in readable format
    void display() const;
        
private:
    void load_from_disk();
    void write_to_disk() const;
    
private:
    DISALLOW_COPY_AND_ASSIGN(Config);
};
} // end namespace detail
} // end namespace okshell


#endif /* CONFIG_H_ */
