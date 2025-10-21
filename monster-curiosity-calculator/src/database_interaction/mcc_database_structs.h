#pragma once
#include <string>
#include <vector>
#include <format>

namespace purple_mb::monster_calculator {

struct TableColumnSchema {
private:
	std::string col_name;
	std::string data_type;
	std::string col_arguments;

public:
	TableColumnSchema() {
		col_name = "";
		data_type = "";
		col_arguments = "";
	}

	TableColumnSchema(std::string name, std::string type, std::string arguments) {
		col_name = name;
		data_type = type;
		col_arguments = arguments;
	}

	std::string GetColumnSchema() {
		return std::vformat("{0} {1} {2}", std::make_format_args(col_name, data_type, col_arguments));
	}

	std::string GetColumnName() {
		return col_name;
	}

	std::string GetDataType() {
		return data_type;
	}

	std::string GetColArguments() {
		return col_arguments;
	}
};

struct TableSchemaList {
private:
	std::vector<TableColumnSchema> col_schemas;

public:
	TableSchemaList(std::vector<TableColumnSchema> cols) {
		col_schemas = cols;
	}

	std::string GetTableSchema() {
		std::string combined_schema = "";
		int col_count = col_schemas.size();
		for (int i = 0; i < col_count; i++) {
			combined_schema += col_schemas[i].GetColumnSchema();
			if (i < col_count - 1) {
				combined_schema += ", ";
			}
		}
		return combined_schema;
	}

	std::vector<std::string> GetTableColNames() {
		std::vector<std::string> col_names = {};

		for (TableColumnSchema schema : col_schemas) {
			col_names.push_back(schema.GetColumnName());
		}

		return col_names;
	}

	TableColumnSchema GetColumnSchema(int column_index) {
		if (column_index < 0 || column_index >= col_schemas.size()) {
			return TableColumnSchema();
		}
		return col_schemas[column_index];
	}
};

} // namespace purple_mb::monster_calculator