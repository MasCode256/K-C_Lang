#include "systems.h"

using namespace std;

string parseArgument(string str) {
	string num = before(str, '.');
	string tpe = after(str, '.');

	if(tpe == "string") {
		return "instruction.args[" + num + "]";
	}

	else return "/*$error*/";
}


int main(int argc, char** argv) {
	cout << "[K-C Codewriter]: Codewriting system is ready!\n";
	
	if(argc > 1) {
		cout << "[K-C Codewriter]: Selected path: " << argv[1] << endl;
		
		const string lexe = "\tbool l_execution(interprier *sys, string pointer, p_instruction instruction) {\n\t\tif(instruction.name == \"null\") return 0;\n\t\t//$end\n\t\telse return 0;\n\t}";
		
		writeFile("libraries\\" + string(argv[1]) + "\\lib.h", "#ifndef LIB" + string(argv[1]) + "_H\n#define LIB" + string(argv[1]) + "_H\nnamespace kcl" + string(argv[1]) + " {\n" + parseString(readFile("libraries\\" + string(argv[1]) + "\\" + parseString(readFile("libraries\\" + string(argv[1]) + "\\lib.kl"), "#include kpp", '\"', '\"')), "sector source", '{', '}') + "\n" + lexe + "}\n#endif");
		replaceSubstringInFile("libraries.h", "//$end", "#include \"libraries\\" + string(argv[1]) + "\\lib.h\"\n//$end");
		replaceSubstringInFile("execution.h", "//$end", "else if(instruction.space == sys->searchLinkName(\"" + string(argv[1]) + "\")){return kcl" + string(argv[1]) + "::l_execution(sys, pointer, instruction);}\n\t//$end");
	
		string src = parseString(readFile("libraries\\" + string(argv[1]) + "\\" + parseString(readFile("libraries\\" + string(argv[1]) + "\\lib.kl"), "#include kpp", '\"', '\"')), "executable", '{', '}');
		vector<string> vexe = splitString2(deleteSym(" \t\n", src), '\n');

		for (size_t i = 0; i < vexe.size(); i++)
		{
			vexe[i] = deleteSym(" \t\n", vexe[i]);
		}
		

		for(int i = 0; i < vexe.size(); i++) {
			cout << "\n[K-C Codewriter]: Vector exe[" << i << "] = " << vexe[i];

			string type = splitString2(vexe[i], ' ')[0];
			string name = deleteSym(" \t", deleteSymFromEnd(" \t", getSubstringBetween(vexe[i], ' ', '=')));
			string srcname = deleteSymFromEnd(" \t", deleteSym(" \t", getSubstringBetween(vexe[i], '=', '(')));

			string ffargs = getSubstringBetween(vexe[i], '(', ')');
			vector<string> fargs = splitString3(ffargs, ',');

			for (size_t j = 0; j < fargs.size(); j++)
			{
				fargs[j] = deleteSymFromEnd(" \t", deleteSym(" \t", fargs[j]));
				cout << "\n[K-C Codewriter]: Arg " << j << ": " << fargs[j] << "";
			}
			

			cout << "\n[K-C Codewriter]: type = " << type << ", srcname = " << srcname;

			if (type == "void") 
			{
				replaceSubstringInFile("libraries\\" + string(argv[1]) + "\\lib.h", "//$end", "if(instruction.name == \"" + name + "\") {" + srcname + "(/*$argend" + numberToString(i) + "*/); return 1;}\n\t\t//$end");
			}
			


			for (size_t j = 0; j < fargs.size(); j++)
			{
				int qcnt = symcnt(fargs[j], '"');
				cout << "\n[K-C Codewriter]: Quote count in vexe[" << i << "].fargs[" << j << "]:" << qcnt;

				if(qcnt == 2) {
					if(j == 0) replaceSubstringInFile("libraries\\" + string(argv[1]) + "\\lib.h", "/*$argend" + numberToString(i) + "*/", fargs[j] + "/*$argend" + numberToString(i) + "*/");
					else replaceSubstringInFile("libraries\\" + string(argv[1]) + "\\lib.h", "/*$argend" + numberToString(i) + "*/", ", " + fargs[j] + "/*$argend" + numberToString(i) + "*/");
				} else {
					fargs[j] = parseArgument(fargs[j]);
					if(j > 0) fargs[j] = ", " + fargs[j];

					replaceSubstringInFile("libraries\\" + string(argv[1]) + "\\lib.h", "/*$argend" + numberToString(i) + "*/", fargs[j] + "/*$argend" + numberToString(i) + "*/");
				}
			}
		}
	}
	
	return 0;
}
