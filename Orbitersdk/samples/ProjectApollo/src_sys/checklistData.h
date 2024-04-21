#pragma once

#include <optional>
#include <string>
#include <vector>

const static std::string CHECKLIST_GROUPS_FILENAME = "GROUPS.tsv";

const static std::vector<std::string> STRING_COLUMN_NAMES = {
	// Main checklist headers
	"Text",
	"Relative Event",
	"Panel",
	"Heading 1",
	"Heading 2",
	"LF",
	"Info",
	"Item",
	"Sound",
	"Call Group",
	"Fail Group",
	"Position",
	"Remarks",
	// Remaining GROUP headers that aren't the same as above
	"Name",
	"Heading",
	"Custom Filename"
};

const static std::vector<std::string> INTEGER_COLUMN_NAMES = {
	// Main checklist headers
	"Time",
	"Automatic",
	// Remaining GROUP headers that aren't the same as above
	"Deadline",
	"Manual",
	"Essential",
	"Slow"
};

// Generic checklist column class, must be inherited
class DataColumn {
};

class LongIntDataColumn : public DataColumn {
public:
	std::vector<std::optional<int64_t>> Data;
};

class StringDataColumn : public DataColumn {
public:
	std::vector<std::optional<std::string>> Data;
};

class DataPage {
public:
	std::map<std::string, StringDataColumn> StringColumns;
	std::map<std::string, LongIntDataColumn> IntegerColumns;
	std::map<int, std::string> ColumnIndexToNameMap;
};