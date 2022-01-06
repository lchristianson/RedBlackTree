#ifndef _PG5_
#define _PG5_

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBHelper.h"
using namespace std;

int main(int argc, char** argv);
bool ProcessCommand();
void Print();
void RPrint();
void AddCommand(string cmd);
void RemoveCommand(string cmd);
void LookupCommand(string cmd);
void EditCommand(string cmd);
#endif