#include <iostream>
#include <map>

class Parser {
public:
    Parser();
    void initializeSymbolTables();
    void showSymbolTables();
    void showInstructions();
    void parseProg();
    void firstPass();
    std::string initializeCinstruction(std::string, bool, bool, bool);

private:
    int cntLines = 0;
    int varNum = 0;
    std::map<int, std::string> instructions;
    std::map<std::string, int> symbolTables;
};