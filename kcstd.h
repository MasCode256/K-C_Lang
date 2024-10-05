// K-C Lang std version 24.09.0.02

#ifndef KCSTD_H
#define KCSTD_H

#include "core.h"
#include "interprier.h"

using namespace std;

void print(string line) {
    cout << line;
}

void printLn(string line) {
    cout << line << endl;
}

void printDln(string line) {
    cout << endl << line << endl;
}

bool std_execute(interprier *sys, string pointer, p_instruction instruction) {
    if(instruction.name == "null" || instruction.name == "") {cout << "\n[Error] 21 null instruction name.\n"; return 1;}
    else if(instruction.name == "print") {if (instruction.args.size() > 0) print(instruction.args[0]); else cout << "\n[Error] 22 null argument list.\n"; return 1;}
    else if(instruction.name == "newVar") {if (instruction.args.size() > 3) sys->newVar(instruction.args[0], instruction.args[1], instruction.args[2], instruction.args[3]); else cout << "\n[Error] 22 small argument list.\n"; return 1;}
    else if(instruction.name == "setVar") {if (instruction.args.size() > 3) sys->setVar(instruction.args[0], instruction.args[1], instruction.args[2]); else cout << "\n[Error] 22 small argument list.\n"; return 1;}
    //$end

    else cout << "\n20 unknown error in std.execution.\n";

    return 0;
}

#endif
