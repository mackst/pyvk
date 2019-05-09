#include "utils.h"

std::vector<const char*> vecStrToVecChar(std::vector<std::string> &strArray)
{
	auto c_str = [](const std::string &s) { return s.c_str(); };
	std::vector<const char*> out(strArray.size());

	std::transform(strArray.begin(), strArray.end(), out.begin(), c_str);

	return out;
}

std::vector<float> vecFloatToVecFloat(std::vector<float>& inArray)
{
	auto toFloat = [](const float &a) { return (float)a; };
	std::vector<float> out(inArray.size());

	std::transform(inArray.begin(), inArray.end(), out.begin(), toFloat);

	return out;
}

