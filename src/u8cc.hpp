#pragma once

#include <ostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]);
int stlMain(std::string&& cmd, std::vector<std::string>&& args);

bool parseArgs(const std::string& cmd, const std::vector<std::string>& args, bool& useFile, bool& doubleSize,
               bool& invertBoard, std::string& file, std::string& fen);
void printUsage(std::ostream& console, const std::string& cmd);
