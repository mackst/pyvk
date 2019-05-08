#include "utils.h"

std::vector<const char*> vecStrToVecChar(std::vector<std::string> &strArray)
{
	auto c_str = [](const std::string &s) { return s.c_str(); };
	std::vector<const char*> out(strArray.size());

	std::transform(strArray.begin(), strArray.end(), out.begin(), c_str);

	return out;
}

