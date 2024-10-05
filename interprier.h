#ifndef INTERPRIER_H
#define INTERPRIER_H

#include "core.h"

using namespace std;

struct name {
    string name;
    string type;
};

struct heap_space {
    vector<string> vars;
    //$end

    vector<name> names;


    void newVar(string vname, string type, string mean) {
    

        vars.push_back(mean);

        cout << "\nNew vector size: " << vars.size();

        name varName;
        varName.name = vname;
        varName.type = type;

        names.push_back(varName);

        cout << "\nSet new " << type << " var with name " << vname << ": " << vars[vars.size() - 1];
    }

    void setVar(string name, string mean) {
        cout << "\nSet var " << " var with name " << name << ": " << mean << endl;
    }

    string getLastVar() {
        cout << "\n[vars.size()] " <<vars.size() << endl;
        return vars[vars.size() - 1];
    }

    int getPoinerByName(string name) {
        for (size_t i = 0; i < names.size(); i++)
        {
            if(names[i].name == name) {
                return i;
            } 
        }

        return 404;
    }

    string getVarByPointer(int index) {
        return vars[index];
    }
};

struct link {
    string name;
    string point;
};

struct function {
    string code;
    heap_space heap;
    vector<heap_space> substack_spaces;
};

struct interprier {
   vector<int> stack;

   heap_space global;
   vector<heap_space> userSpaces;
   vector<function> functions;

   vector<link> links;


   string searchLinkName(string point) {
        for (size_t i = 0; i < links.size(); i++)
        {
            if(links[i].point == point) {
                return links[i].name;
            }
        }
        return "null";
   }


   void newVar(string type, string name, string space, string mean) {
        if(space == "current") {
            if(functions.size() > 0) {
                functions[functions.size() - 1].heap.newVar(name, type, mean);
            } else {
                cout << "\n23 not functions to set new var.\n";
            }
        }
   }

   void setVar(string name, string space, string mean) {
        if(space == "current") {
            if(functions.size() > 0) {
                functions[functions.size() - 1].heap.setVar(name, mean);
            } else {
                cout << "\n23 not functions to set new var.\n";
            }
        }
   }

   string main(int argc, char** argv) {
    
   }
};

struct p_instruction {
    string name;
    string space;

    vector<string> args;

    void parseInstruction(string str) {

    }
};




#endif