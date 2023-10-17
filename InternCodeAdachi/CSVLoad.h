#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string ReadDataFromCSV(const char* _FileName, unsigned int ReadRow);

std::vector<std::string> SeparateString(std::string _str, char _Separatechar);