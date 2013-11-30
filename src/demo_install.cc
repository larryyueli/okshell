/*
 * demo_install.cc
 * Demo the installation process of OkShell
 *
 *  Created on: 2013-11-30
 *      Author: Larry Yueli Zhang
 */

#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

int main()
{
    cout << "\nInstalling OkShell..." << endl;
    usleep(1500000);
    cout << "Done. Type `ok` to get started.\n" << endl;
}
