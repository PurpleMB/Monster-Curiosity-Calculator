#pragma once
#include <string>
#include <vector>
#include <format>

#include "mcc_display_structs.h"
#include "mcc_display_constants.h"

namespace monster_calculator {

struct ValueOperationArgument {
	std::string display_name;
	std::string database_name;
	DisplayColor argument_color;

	ValueOperationArgument() {
		display_name = "";
		database_name = "";
		argument_color = kFuschiaColor;
	}

	ValueOperationArgument(std::string dis_name, std::string db_name, DisplayColor color) {
		display_name = dis_name;
		database_name = db_name;
		argument_color = color;
	}
};

struct ValueOperation {
	std::string display_name;
	std::string select_format;
	std::string group_format;
	std::string order_format;
	std::string alias_format;
	DisplayColor operation_color;
	std::vector<ValueOperationArgument> arguments;

	ValueOperation() {
		display_name = "";
		select_format = "";
		group_format = "";
		order_format = "";
		alias_format = "";
		operation_color = kFuschiaColor;
		arguments = { ValueOperationArgument() };
	}

	ValueOperation(std::string dis_name, std::string select_f, std::string group_f, std::string order_f,
		std::string alias_f, DisplayColor color, std::vector<ValueOperationArgument> args) {
		display_name = dis_name;
		select_format = select_f;
		group_format = group_f;
		order_format = order_f;
		alias_format = alias_f;
		operation_color = color;
		arguments = args;
	}
};

struct ValueQuery {
private:
	//const std::string subquery_format = "(SELECT {0} FROM {1} GROUP BY {2} ORDER BY {3}) as {4}";
	
public:
	std::string select_statement;
	std::string group_statement;
	std::string order_statement;
	std::string value_alias;


	ValueQuery() {
		select_statement = "";
		group_statement = "";
		order_statement = "";
		value_alias = "";
	}

	std::string GenerateQueryStatement(std::string table_name) {
		if (select_statement.size() == 0 || value_alias.size() == 0) {
			return "";
		}

		std::string query = "";
		query += std::vformat("(SELECT {0}", std::make_format_args(select_statement));
		query += std::vformat(" FROM {0}", std::make_format_args(table_name));

		if (group_statement.size() > 0) {
			query += std::vformat(" GROUP BY {0}", std::make_format_args(group_statement));
		}
		if (order_statement.size() > 0) {
			query += std::vformat(" ORDER BY {0}", std::make_format_args(order_statement));
		}

		query += std::vformat(") AS {0}", std::make_format_args(value_alias));

		return query;
	}
};

} // namespace monster_calculator