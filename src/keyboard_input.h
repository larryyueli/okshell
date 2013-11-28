/*
 * keyboard_input.h
 * classes used to collect and validate keyboard input
 *
 *  Created on: 2013-11-21
 *      Author: Larry Yueli Zhang
 */

#ifndef KEYBOARD_INPUT_H_
#define KEYBOARD_INPUT_H_

#include <string>
#include "common_defs.h"

namespace okshell
{
namespace detail
{
using std::string;

// Based class of input validators.
template <typename T>
class InputValidatorBase
{
public:
    InputValidatorBase() {}
    virtual ~InputValidatorBase () {}
    
public:
    // return value: whether validation succeeded.
    // result: the casted result to pass to keyboard_input
    // error_message: error message when validation fails, 
    // error_message is empty string if success.
    virtual bool validate(const string& input, T& result, 
            string& error_message) = 0;

private:
    DISALLOW_COPY_AND_ASSIGN(InputValidatorBase);
};

// The function called to get a valid keyboard input
// Return default value when input is empty
// On invalid input, retry untils the input is valid
template <typename T>
T keyboard_input(const string& prompt_message, bool with_default, 
        const T& default_value, InputValidatorBase<T>* validator);

// Input validator that checks the input of choices from 
// an integer labelled menu
class IntegerChoiceInputValidator : public InputValidatorBase<size_t>
{
public:
    // n_choices is the total number of choices
    IntegerChoiceInputValidator(size_t n_choices);

private:
    size_t n_choices_; // number of choices
    
public:
    bool validate(const string& input, size_t& result, string& error_message);  
};

// Input validator the checks the answer of a yes or no questions.
// Valid input: y, n, yes, no
// Possible result: "y" or "n"
class YesNoInputValidator : public InputValidatorBase<string>
{
public:
    YesNoInputValidator() {}
    
public:
    bool validate(const string& input, string& result, string& error_message);  
};

// Input validator that checks the input when manually adding commands
// check if the string has unclosed argument brackets <arg1>
class CommandInputValidator : public InputValidatorBase<string>
{
public:
    CommandInputValidator() {}
    
public:
    bool validate(const string& input, string& result, string& error_message);
};

// wrappers that include the keyboard_input call with validator
// Interger choice wrapper, always has default value
size_t integer_choice_input(const string& prompt_message, 
        const size_t& default_value, size_t n_choices);

// Yes/No wrapper, always has default value
string yes_no_input(const string& prompt_message, const string& default_value);

// CommandInput always no default value
string command_input(const string& prompt_message);

} // end namespace detail
} // end namespace okshell

#endif /* KEYBOARD_INPUT_H_ */
