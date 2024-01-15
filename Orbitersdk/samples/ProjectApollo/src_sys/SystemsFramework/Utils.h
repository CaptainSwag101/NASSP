#pragma once

#include <string>

static std::string trim(const std::string& str, const std::string& trimChars = "<> \t\r\n")
{
	const auto strBegin = str.find_first_not_of(trimChars);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(trimChars);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}