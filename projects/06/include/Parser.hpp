#include <iostream>
#include <map>

class Parser {
public:
    Parser();
    void initializeSymbolTables();
    void showSymbolTables();
    void parseProg();
    std::string initializeCinstruction(std::string, bool, bool, bool);

private:
    int cntLines = 0;
    std::map<int, std::string> instructions;
    std::map<std::string, int> symbolTables;
};