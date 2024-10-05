#ifndef SYSTEMS_H
#define SYSTEMS_H


#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool containsSubstring(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

void replaceSubstringInFile(const std::string& filename, const std::string& oldSubstr, const std::string& newSubstr) {
    std::ifstream fileIn(filename.c_str());
    if (!fileIn) {
        std::cerr << "Canntot replace substring in file: " << filename << std::endl;
        return;
    }

    std::string content;
    std::string line;
    while (std::getline(fileIn, line)) {
        size_t pos = 0;
        while ((pos = line.find(oldSubstr, pos)) != std::string::npos) {
            line.replace(pos, oldSubstr.length(), newSubstr);
            pos += newSubstr.length();
        }
        content += line + "\n";
    }
    fileIn.close();

    std::ofstream fileOut(filename.c_str());
    if (!fileOut) {
        std::cerr << "Cannot write to file: " << filename << std::endl;
        return;
    }

    fileOut << content;
    fileOut.close();
}

std::string parseString(const std::string& str, const std::string& substr, char sym1, char sym2) {
    // ����� ������� ���������
    size_t substrPos = str.find(substr);
    if (substrPos == std::string::npos) {
        return ""; // ��������� �� �������
    }

    // ����� ������� ������� ������� ����� ���������
    size_t sym1Pos = str.find(sym1, substrPos);
    if (sym1Pos == std::string::npos) {
        return ""; // ������ ������ �� ������
    }

    // ���� sym1 � sym2 ���������, ���� ��������� ���������
    if (sym1 == sym2) {
        size_t sym2Pos = str.find(sym2, sym1Pos + 1);
        if (sym2Pos == std::string::npos) {
            return ""; // ������ ������ �� ������
        }
        return str.substr(sym1Pos + 1, sym2Pos - sym1Pos - 1);
    }

    // ������������ ������� ��� ������������ �����������
    int depth = 0;
    size_t startPos = sym1Pos + 1;

    for (size_t i = startPos; i < str.length(); ++i) {
        if (str[i] == sym1) {
            ++depth;
        } else if (str[i] == sym2) {
            if (depth == 0) {
                // ������ ��������������� ����������� ������
                return str.substr(startPos, i - startPos);
            } else {
                --depth;
            }
        }
    }

    return ""; // ��������������� ����������� ������ �� ������
}




std::string readFile(const std::string& filename) {
    std::ifstream inFile(filename.c_str(), std::ios::in);
    if (!inFile) {
        std::cerr << "Cannot open the file." << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(inFile)),
                        std::istreambuf_iterator<char>());

    inFile.close();
    return content;
}

void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename.c_str(), std::ios::out);

    if (!outFile) {
        std::cerr << "Cannot write to file." << std::endl;
        return;
    }

    outFile << content;

    outFile.close();
}

std::string numberToString(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

int strToNum(string str) {
    int num;
    std::stringstream(str) >> num;

    return num;
}

string before(string str, char sym) {
    string ret = "";

    for(int i = 0; i < str.length() - 1; i++) {
        if(str[i] == sym) break;
        ret += str[i];
    }

    return ret;
}

string after(string str, char sym) {
    for (size_t i = 0; i < str.length(); i++)
    {
        if(str[i] == sym) {
            string ret = "";
            for (size_t j = i + 1; j < str.length(); j++)
            {
                ret += str[j];
            }

            return ret;
            
        }
    }

    return "/*$error*/";
    
}

std::vector<std::string> splitString(const std::string& str, char delimiter, char openChar, char closeChar) {
    std::vector<std::string> result;
    std::string token;
    bool insideBraces = false;

    for (std::string::size_type i = 0; i < str.size(); ++i) {
        char ch = str[i];

        if (ch == openChar) {
            insideBraces = true;
            token += ch;  // Добавляем открывающий символ
        } else if (ch == closeChar) {
            token += ch;  // Добавляем закрывающий символ
            insideBraces = false;
        } else if (ch == delimiter && !insideBraces) {
            if (!token.empty()) {
                result.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }

    if (!token.empty()) {
        result.push_back(token);
    }

    return result;
}

std::string deleteSym(const std::string& symList, const std::string& str) {
    std::string result;
    bool deleteMode = true;

    for (std::string::size_type i = 0; i < str.length(); ++i) {
        char ch = str[i];
        if (deleteMode && symList.find(ch) != std::string::npos) {
            continue; // Пропускаем символы, которые есть в symList
        } else {
            deleteMode = false; // Переключаемся в режим сохранения
            result += ch;
        }
    }

    return result;
}

std::string deleteSymFromEnd(const std::string& symList, const std::string& str) {
    std::string result;
    bool deleteMode = true;

    for (std::string::size_type i = str.length(); i-- > 0; ) { // Обратите внимание на i--
        char ch = str[i];
        if (deleteMode && symList.find(ch) != std::string::npos) {
            // Пропускаем символы, которые есть в symList
            continue;
        } else {
            deleteMode = false; // Переключаемся в режим сохранения
            result = ch + result; // Добавляем в начало строки
        }
    }

    return result;
}

std::string removeLeadingTabs(const std::string& content) {
    std::istringstream stream(content);
    std::string line;
    std::string result;
    int minTabs = -1;

    // Определяем минимальное количество начальных табуляций
    while (std::getline(stream, line)) {
        int count = 0;
        while (count < line.size() && line[count] == '\t') {
            ++count;
        }
        if (minTabs == -1 || count < minTabs) {
            minTabs = count;
        }
    }

    // Сброс потока для повторного чтения
    stream.clear();
    stream.seekg(0, std::ios::beg);

    // Удаляем начальные табуляции
    while (std::getline(stream, line)) {
        if (line.size() >= minTabs) {
            result += line.substr(minTabs) + '\n';
        } else {
            result += line + '\n';
        }
    }

    return result;
}

std::vector<std::string> splitString2(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

std::string joinStrings(const std::vector<std::string>& strings, const std::string& delimiter) {
    std::ostringstream result;
    for (size_t i = 0; i < strings.size(); ++i) {
        result << strings[i];
        if (i < strings.size() - 1) {
            result << delimiter;
        }
    }
    return result.str();
}

string tabdelete(string str) {
    vector<string> strs = splitString2(str, '\n');
    //int progress = 0;

    for(int i = 0; i < strs.size(); i++) {
        /*for (size_t j = 0; j < strs[i].length(); j++)
        {
            if(strs[i][j] != '\t') {
                strs[i].erase(0, 1);
                progress++;
                continue;
            } else if (strs[i][j] == '\t') {
                strs[i].erase(0, 1);
                progress += 4;
                continue;
            }
        }
        if (progress >= 8) continue;*/
        strs[i].erase(0, 8);
    }

    return joinStrings(strs, "\n");
}

int symcnt(string str, char sym) {
    int ret = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if(str[i] == sym) ret++;
    }
    
    return ret;
}

std::string getSubstringBetween(const std::string& str, char startChar, char endChar) {
    // Найти позиции начального и конечного символов
    size_t startPos = str.find(startChar);
    size_t endPos = str.find(endChar, startPos + 1);
    
    // Проверить, что оба символа найдены
    if (startPos == std::string::npos || endPos == std::string::npos || startPos >= endPos) {
        return ""; // Возвращаем пустую строку, если не удалось найти подстроку
    }
    
    // Извлечь подстроку между startChar и endChar
    return str.substr(startPos + 1, endPos - startPos - 1);
}

std::vector<std::string> splitStringImproved(const std::string& str, char delimiter, char startSymbol, char endSymbol) {
    std::vector<std::string> result;
    std::string currentPart;
    bool insideSymbols = false;

    for (char ch : str) {
        if (ch == startSymbol) {
            insideSymbols = true;
            currentPart += ch;
        }
        else if (ch == endSymbol) {
            insideSymbols = false;
            currentPart += ch;
            result.push_back(currentPart);
            currentPart.clear();
        }
        else if (ch == delimiter &&!insideSymbols) {
            if (!currentPart.empty()) {
                result.push_back(currentPart);
                currentPart.clear();
            }
        }
        else {
            currentPart += ch;
        }
    }

    if (!currentPart.empty()) {
        result.push_back(currentPart);
    }

    return result;
}

std::vector<std::string> splitString3(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string item;
    bool insideQuotes = false;

    for (char c : str) {
        if (c == '"') {
            insideQuotes =!insideQuotes;
            item += c; // Добавляем кавычки в элемент
        } else if (c == delimiter &&!insideQuotes) {
            result.push_back(item);
            item.clear();
        } else {
            item += c;
        }
    }

    // Не забываем добавить последний элемент
    if (!item.empty()) {
        result.push_back(item);
    }

    return result;
}


#endif
