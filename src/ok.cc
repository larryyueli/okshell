/*
 * ok.cc
 * The main file for the ok executable.
 *
 *  Created on: 2013-10-25
 *      Author: Larry Yueli Zhang
 */

#include <string>
#include <vector>
#include "okshell.h"

using std::string;
using std::vector;

int main(int argc, char **argv)
{
    vector<string> args;
    for (int i = 0; i < argc; ++i)
        args.push_back(argv[i]);
    okshell::OkShell oks{};
    int ret = oks.run(args);
    return ret;
}
