#include "systems.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	if (argc > 1) {
		cout << "[K-C Sourcemodule]: Argument 1: " << string(argv[1]) << endl;
		
		string code = readFile(string(argv[1]));
		
		if (containsSubstring(code, "#source")) {
			cout << "[K-C Sourcemodule]: " << string(argv[1]) << " is source library file and loaded to pluginslot " << parseString(code, "#source", '\"', '\"');
		} else {
			cout << "[K-C Sourcemodule]: " << string(argv[1]) << " is NOT source .kl file.\n";
			
			if (containsSubstring(code, "#type \"plugin\"")) {
				cout << "[K-C Sourcemodule]: opening kcompress with type 'plugin'..." ;

				string spos = readFile("libraries\\pos.dat");
				int pos = strToNum(spos) + 1;
				spos = numberToString(pos);
				writeFile("libraries\\pos.dat", spos);

				cout << "\n[cmd]: "; system(("mkdir libraries\\" + spos).c_str());

				string compress = parseString(code, "compress", '{', '}');
				vector<string> parts = splitString(compress, ',', '{', '}');

				for(int i = 0; i < parts.size(); i++) {
					string name = parseString(parts[i], "file", '\"', '\"');
					string content = removeLeadingTabs(parseString(parts[i], "write", '{', '}'));

					writeFile("libraries\\" + spos + "\\" + name, tabdelete(deleteSym("\n", content)));
					cout << "\n[K-C Decompressor]: Writing content to file " << "libraries\\" + spos + "\\" + name << endl;
					cout << "[Debug]: content: " << deleteSym("\n\t ", content) << endl;
					cout << "[Debug]: part: " << parts[i] << endl;
				}

				writeFile(string(argv[1]), "#source \"" + spos + "\"");
			}
		}
	
}
	return 0;
}
