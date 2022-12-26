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

void Parser::showInstructions() {
    for (auto el : instructions) {
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

std::string& trim(std::string &s) {
    if (!s.empty()) {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }
    return s;
}

Parser::Parser() : cntLines(0), varNum(0) {
    Parser::initializeSymbolTables();
    std::ifstream ifs;
    ifs.open("/home/ylf/nand2tetris/projects/06/max/Max.asm", std::ifstream::in);
    if (!ifs.is_open()) return;

    // First Pass
    std::string line;
    cntLines = 0;

    while(std::getline(ifs, line)) {
        line = trim(line);
        int length = line.length();
        if (line == "") continue;
        else if (line.length() > 2 && line[0] == '/' && line[1] == '/') continue; 
        else if (length > 1 && line[0] == '(') {
            std::string symbol = line.substr(1, length - 2);
            //std::cout << symbol << std::endl;
            symbolTables[symbol] = cntLines;
        } 
        else cntLines++;
    }
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    cntLines = 0;

    // Second Pass
    while(std::getline(ifs, line)) {
        line = trim(line);
        if (line == "") continue;
        if (line.length() > 2 && line[0] == '/' && line[1] == '/') continue; 
        int length = line.length();
        if (line[0] == '@') {
            int len = line.length() - 1;
            std::string var = line.substr(1, len);
            try {
                std::stoi(var);
            } catch(...) {
                if (symbolTables.count(var)) continue;
                symbolTables[var] = varNum++;
                //std::cout << var << std::endl;
            }
        }
        cntLines++;
    }
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    cntLines = 0;

    while(std::getline(ifs, line)) {
        if (line.find("//") != line.npos) 
            line = line.substr(0, line.find("//"));
        line = trim(line);
        if (line == "") continue;
        if (line.length() > 1 && line[0] == '(') continue;
        if (line.length() > 2 && line[0] == '/' && line[1] == '/') continue;
        if (line.find("//") != line.npos) 
            line = line.substr(0, line.find("//"));
        //std::cout << line << std::endl;
        if (line[0] == '@') {
           int len = line.length() - 1;
            std::string var = line.substr(1, len);
            try {
                std::stoi(var);
            } catch(...) {
               line = "@" + std::to_string(symbolTables[var]);
            } 
        }
        instructions[cntLines++] = line;
    }
    // Parser::showSymbolTables();
    // Parser::showInstructions();
}

void Parser::parseProg() {
    for (int i = 0; i < cntLines; i ++) {
        std::string ins = instructions[i];
        if (ins[0] == '@') { // A instruction
            int len = ins.length() - 1;
            int num = std::stoi(ins.substr(1, len));
            const int n = 15;
            std::string bin = std::bitset<n>(num).to_string();
            bin.insert(0, "0");
            std::cout << bin << std::endl;
        } else {             // C instruction
            if (ins.find("=") != ins.npos) {
                int pos = ins.find("=");
                std::string dest = ins.substr(0, pos);
                std::string comp = ins.substr(pos + 1, ins.length() - pos - 1);
                //std::cout << dest << " " << comp << std::endl;
                std::cout << "111" + Parser::initializeCinstruction(comp, true, false, false) + 
                Parser::initializeCinstruction(dest, false, true, false) + "000" << std::endl;
            }
            else if (ins.find(";") != ins.npos) {
               int pos = ins.find(";");
                std::string comp = ins.substr(0, pos);
                std::string jump = ins.substr(pos + 1, ins.length() - pos - 1);
                //std::cout << dest << " " << comp << std::endl;
                std::cout << "111" + Parser::initializeCinstruction(comp, true, false, false) + "000" +
                Parser::initializeCinstruction(jump, false, false, true) << std::endl; 
            }
        }
    }
}