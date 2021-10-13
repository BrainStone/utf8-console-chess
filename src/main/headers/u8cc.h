#pragma once

#include <string>
#include <vector>

int main(int argc, char* argv[]);
int stlMain(std::string&& cmd, std::vector<std::string>&& args);
int stlWMain(std::wstring&& cmd, std::vector<std::wstring>&& args);
