#pragma once

#include <string>
#include <vector>

int main(int argc, char* argv[]);
int stdMain(std::string&& cmd, std::vector<std::string>&& args);
int stdWMain(std::wstring&& cmd, std::vector<std::wstring>&& args);
