#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <sys/stat.h> // Для mkdir

#ifdef _WIN32
#include <direct.h> // Для _mkdir на Windows
#define MKDIR(dir) _mkdir(dir)
#else
#define MKDIR(dir) mkdir(dir, 0755)
#endif

using namespace std;

std::string numberToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

bool createDirectory(const std::string& path) {
    return MKDIR(path.c_str()) == 0 || errno == EEXIST;
}

void replace(const std::string& from, const std::string& to, bool debug) {
	if (debug) cout << "\n[Debug]: replacing from " << from << " to " << to;
	
    std::ifstream fin(from.c_str());
    std::ofstream fout(to.c_str(), std::ios::out | std::ios::trunc);
    
    char c;
    while (fin.get(c)) {
        fout << c;
    }
    
    fin.close();
    fout.close();
}

int main(int argc, char** argv) {
    cout << "[K-C Backup system]: Backuper is ready!\n";
    cout << "[K-C Backup system]: Argument '1': " << argv[1] << endl;
    
    if (argc == 1) {
    	argc++;
    	argv[1] = "replace";
	}
    
    if (argc > 1 && string(argv[1]) == "replace") {
        cout << "\n[K-C Backup system]: Replace mode is active!" << endl;
        
        if(argc < 3) {
        	cout << "[K-C Backup system]: Replace submode: basic";
        	
        	replace("backups\\system\\main.cpp", "main.cpp", true);
        	
        	replace("backups\\system\\core.h", "core.h", true);
        	replace("backups\\system\\kcstd.h", "kcstd.h", true);
        	replace("backups\\system\\libraries.h", "libraries.h", true);
        	replace("backups\\system\\includes.h", "includes.h", true);
		} 
        
        if (argc > 2 && string(argv[2]) == "last") {
            cout << "[K-C Backup system]: Replace submode: last-backup";

            string spos = "system";
            ifstream pfin("backups\\pos.dat");

            if(!(!pfin)) {
                pfin >> spos;
            } else {
                cout << "[WARNING]: Not enough backups. Loading system backup...\n";
            }
        	
        	replace("backups\\" + spos + "\\main.cpp", "main.cpp", true);
        	
        	replace("backups\\" + spos + "\\core.h", "core.h", true);
        	replace("backups\\" + spos + "\\kcstd.h", "kcstd.h", true);
        	replace("backups\\" + spos + "\\libraries.h", "libraries.h", true);
        	replace("backups\\" + spos + "\\includes.h", "includes.h", true);
        }
    }
    
    if (argc > 1 && string(argv[1]) == "add") {
        cout << "[K-C Backup system]: Adding mode is active!" << endl /*<< "[K-C System]: Launching system-0"*/;
        /*
        ifstream pos("backups\\pos.data");
        if(!pos) {
        	pos.close();
        	
        	ofstream pos("backups\\pos.data");
        	pos << 0;

            pos.close();
		}
        long unsigned int ips = 0;

        pos.close();
        ifstream pos2("backups\\pos.data");
        pos2 >> ips;
        pos2.close();

		
		string spos = numberToString(ips);
        
        if(argc < 3) {
        	cout << "[K-C Backup system]: Adding submode: basic\n";
            cout << "[MKDIR]: Creating directory result: " << createDirectory("backups\\" + spos);
            
            ofstream main(("backups\\" + spos + "\\main.cpp").c_str()); main.close();
        	
        	replace("main.cpp", "backups\\" + spos + "\\main.cpp", true);
        	replace("core.h", "backups\\" + spos + "\\core.h", true);
        	replace("kcstd.h", "backups\\" + spos + "\\kcstd.h", true);
        	replace("libraries.h", "backups\\" + spos + "\\libraries.h", true);
        	replace("includes.h", "backups\\" + spos + "\\includes.h", true);

            ips++;
            ofstream pos("backups\\pos.data");
            pos << ips;
            pos.close();
		}*/

        //cout << "[CMD]: ";
        if (argc < 3) {
            int pos = 0;

            fstream pfin("backups\\pos.dat", ios::in);
            if (!pfin) {
                // Если файл не существует, создаем его и записываем 0
                ofstream pfout("backups\\pos.dat");
                pfout << "0";
                pfout.close();
            } else {
                // Читаем текущее значение
                pfin >> pos;
                pfin.close();

                // Увеличиваем значение или сбрасываем до 0
                if (pos >= 2) {
                    pos = 0;
                } else {
                    pos += 1;
                }

                // Открываем файл для записи и обновляем значение
                ofstream pfout("backups\\pos.dat");
                pfout << pos;
                pfout.close();
            }

            string dirName = "backups\\" + numberToString(pos);
            string command = "mkdir \"" + dirName + "\"";
            system(command.c_str());

            command = "copy main.cpp \"" + dirName + "\\\"";
            cout << "[cmd]: "; system(command.c_str());

            command = "copy core.h \"" + dirName + "\\\"";
            cout << "[cmd]: "; system(command.c_str());

            command = "copy includes.h \"" + dirName + "\\\"";
            cout << "[cmd]: "; system(command.c_str());

            command = "copy kcstd.h \"" + dirName + "\\\"";
            cout << "[cmd]: "; system(command.c_str());

            command = "copy libraries.h \"" + dirName + "\\\"";
            cout << "[cmd]: "; system(command.c_str());
        }
    }
    
    return 0;
}

