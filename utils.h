#pragma once

#ifndef UTILS_H
#define UTILS_H


#include <fstream>
#include <algorithm>
#include <string>
#include <vector>


std::vector<const char*> vecStrToVecChar(std::vector<std::string> &strArray);

std::vector<float> vecFloatToVecFloat(std::vector<float> &inArray);

std::vector<char> readFile(const std::string& filename);


#endif // !UTILS_H
