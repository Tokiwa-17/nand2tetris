#include <iostream>
#include <fstream>
#include <bitset>
#include "Parser.hpp"

void Parser::initializeSymbolTables() {
    symbolTables.clear();
    for(int i = 0; i < 16; i++) {
        std::string symbol = "R" + std::to_string(i);
        symbolTables[symbol] = i;
    }   
    symbolTables["SCREEN"] = 16384;
    symbolTables["KBD"] = 24576;
    symbolTables["SP"] = 0;
    symbolTables["LCL"] = 1;
    symbolTables["ARG"] = 2;
    symbolTables["THIS"] = 3;
    symbolTables["THAT"] = 4;
    symbolTables["LOOP"] = 4;
    symbolTables["STOP"] = 18;
    symbolTables["END"] = 22;
    symbolTables["i"] = 16;
    symbolTables["sum"] = 17;
}

void Parser::showSymbolTables() {
    for(auto el : symbolTables) {
        std::cout << el.first << " " << el.second << std::endl;
    }
}

Parser::Parser() : cntLines(0) {
    std::ifstream ifs;
    ifs.open("/home/ylf/nand2tetris/projects/06/src/Add.asm", std::ifstream::in);
    if (!ifs.is_open()) return;
    std::string line;
    while(std::getline(ifs, line)) {
        if(line == "\r") continue;
        if(line.length() > 2 && line[0] == '/' && line[1] == '/') continue;
        std::cout << line << std::endl;
        instructions[cntLines++] = line;
    }
    Parser::initializeSymbolTables();
    //Parser::showSymbolTables();
}

void Parser::parseProg() {
    for (int i = 0; i < cntLines; i ++) {
        std::string ins = instructions[i];
        if (ins[0] == '@') { // A instruction
            int len = ins.length() - 2;
            int num = std::stoi(ins.substr(1, len));
            const int n = 15;
            std::string bin = std::bitset<n>(num).to_string();
            bin.insert(0, "0");
            std::cout << bin << std::endl;
        } else {             // C instruction
            
        }
    }
}