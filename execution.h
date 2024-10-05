#ifndef EXECUTION_H
#define EXECUTION_H

#include "core.h"

bool execute(interprier *sys, string pointer, p_instruction instruction) {
	//cout << "Launching executer...\n";
    if(instruction.space == "" || instruction.space == "std") {return std_execute(sys, pointer, instruction);}
    else if(instruction.space == sys->searchLinkName("4")){return kcl4::l_execution(sys, pointer, instruction);}
	else if(instruction.space == sys->searchLinkName("4")){return kcl4::l_execution(sys, pointer, instruction);}
	else if(instruction.space == sys->searchLinkName("4")){return kcl4::l_execution(sys, pointer, instruction);}
	else if(instruction.space == sys->searchLinkName("4")){return kcl4::l_execution(sys, pointer, instruction);}
	//$end

    else {cout << "11 null execution space."; return 0; }
}

#endif
