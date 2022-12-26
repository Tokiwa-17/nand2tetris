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

std::string Parser::initializeCinstruction(std::string s, bool comp, bool dest, bool jump) {
    if (comp) {
        if (s == "0")       return "0101010";
        else if (s == "1")  return "0111111";
        else if (s == "-1") return "0111010";
        else if (s == "D")  return "0001100";
        else if (s == "A")  return "0110000";
        else if (s == "!D") return "0001101";
        else if (s == "!A") return "0110001";
        else if (s == "-D") return "0001111";
        else if (s == "-A") return "0110011";
        else if (s == "D+1")return "0011111";
        else if (s == "A+1")return "0110111";
        else if (s == "D-1")return "0001110";
        else if (s == "A-1")return "0110010";
        else if (s == "D+A")return "0000010";
        else if (s == "D-A")return "0010011";
        else if (s == "A-D")return "0000111";
        else if (s == "D&A")return "0000000";
        else if (s == "D|A")return "0010101";
        else if (s == "M")  return "1110000";
        else if (s == "!M") return "1110001";
        else if (s == "-M") return "1110011";
        else if (s == "M+1")return "1110111";
        else if (s == "M-1")return "1110010";
        else if (s == "D+M")return "1000010";
        else if (s == "D-M")return "1010011";
        else if (s == "M-D")return "1000111";
        else if (s == "D&M")return "1000000";
        else if (s == "D|M")return "1010101";
    } else if (dest) {
        if (s == "M")       return "001";
        else if (s == "D")  return "010";
        else if (s == "MD") return "011";
        else if (s == "A")  return "100";
        else if (s == "AM") return "101";
        else if (s == "AD") return "110";
        else if (s == "AMD")return "111";
        else                return "000";
    } else {
        if (s == "JGT") return "001";
        else if (s == "JEQ") return "010";
        else if (s == "JGE") return "011";
        else if (s == "JLT") return "100";
        else if (s == "JNE") return "101";
        else if (s == "JLE") return "110";
        else if (s == "JMP") return "111";
        else return "000";
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
        //std::cout << line << std::endl;
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
            if (ins.find("=") != ins.npos) {
                int pos = ins.find("=");
                std::string ins_ = ins.substr(0, ins.length() - 1);
                std::string dest = ins_.substr(0, pos);
                std::string comp = ins_.substr(pos + 1);
                //std::cout << dest << " " << comp << std::endl;
                std::cout << "111" + Parser::initializeCinstruction(comp, true, false, false) + 
                Parser::initializeCinstruction(dest, false, true, false) + "000" << std::endl;
            }
            if (ins.find(";") != ins.npos) {

            }
        }
    }
}