#pragma once

#include <optional>
#include <string>
#include <vector>

const std::vector<std::string> STRING_COLUMN_NAMES = {
	// Main checklist headers
	"Text",
	"Relative Event",
	"Panel",
	"Heading 1",
	"Heading 2",
	"LF",
	"Info",
	"Item",
	"Call Group",
	"Fail Group",
	"Remarks",
	// Remaining GROUP headers that aren't the same as above
	"Name",
	"Heading",
};

const std::vector<std::string> INTEGER_COLUMN_NAMES = {
	// Main checklist headers
	"Time",
	"Position",
	"Automatic",
	// Remaining GROUP headers that aren't the same as above
	"Deadline",
	"Manual",
	"Essential",
	"Sound",
	"Slow",
};

// Generic checklist column class, must be inherited
class DataColumn {
public:
	std::string Name;
};

class LongIntDataColumn : public DataColumn {
public:
	std::vector<std::optional<int64_t>> Data;
};

class StringDataColumn : public DataColumn {
public:
	std::vector<std::optional<std::string>> Data;
};