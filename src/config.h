/*
 * config.h
 * The class that stores the configurations
 *
 *  Created on: 2013-11-29
 *      Author: Larry Yueli Zhang
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
using std::map;
using std::string;

// impl is map from key to value
class ConfigFile
{
public:
    ConfigFile () {}
    
private:
    map<string, string>     impl_;

public:
    // return whether the key exists
    bool get_value(const string& key, string& value) const;
    
    // add the key value if key does not exists
    // overwrite the value if key already exists
    void add_update_key_value(const string& key, const string& value);
    
    void load_from_disk(const string& filename);
    void write_to_disk(const string& filename) const;
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
    
private:
    void load_from_disk();
    void write_to_disk() const;
};
} // end namespace detail
} // end namespace okshell


#endif /* CONFIG_H_ */
