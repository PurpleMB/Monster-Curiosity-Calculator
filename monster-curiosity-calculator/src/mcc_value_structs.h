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

struct ValueOperation_Defunct {
	std::string display_name;
	std::string select_format;
	std::string group_format;
	std::string order_format;
	std::string alias_format;
	DisplayColor operation_color;
	std::vector<ValueOperationArgument> arguments;

	ValueOperation_Defunct() {
		display_name = "";
		select_format = "";
		group_format = "";
		order_format = "";
		alias_format = "";
		operation_color = kFuschiaColor;
		arguments = { ValueOperationArgument() };
	}

	ValueOperation_Defunct(std::string dis_name, std::string select_f, std::string group_f, std::string order_f,
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

struct ValueOperation {
private:
	std::string display_name;
	DisplayColor display_color;

	// this string is expected to be ready for a vformat call with 2 args, the first representing a column name, and the second being the table name
	// the GenerateArgumentQuery function fills in the column name slots, replacing the table name slots with {0} so that they may be filled later
	std::string query_format;
	std::string alias_format;

	std::vector<ValueOperationArgument> arguments;

public:

	ValueOperation() {
		display_name = "";
		query_format = "";
		display_color = kFuschiaColor;
		arguments = {ValueOperationArgument()};
	}

	ValueOperation(std::string name, std::string query, std::string alias, DisplayColor color, std::vector<ValueOperationArgument> args) {
		display_name = name;
		query_format = query;
		alias_format = alias;
		display_color = color;
		arguments = args;
	}

	std::string GetDisplayName() {
		return display_name;
	}

	DisplayColor GetDisplayColor() {
		return display_color;
	}

	std::vector<ValueOperationArgument> GetArgumentList() {
		return arguments;
	}

	std::string GenerateArgumentQuery(ValueOperationArgument argument) {
		std::string arg_query_format = query_format;
		std::string arg_db_name = argument.database_name;
		// we change all {1} to {0} so that the target table name can be formatted in later
		arg_query_format = std::vformat(arg_query_format, std::make_format_args(arg_db_name, "{0}"));
		return arg_query_format;
	}

	std::string GenerateArgumentAlias(ValueOperationArgument argument) {
		std::string alias = alias_format;
		std::string arg_db_name = argument.database_name;
		alias = std::vformat(alias, std::make_format_args(arg_db_name));
		return alias;
	}
};

struct ValueQuery_Defunct {
private:
	//const std::string subquery_format = "(SELECT {0} FROM {1} GROUP BY {2} ORDER BY {3}) as {4}";
	
public:
	std::string select_statement;
	std::string group_statement;
	std::string order_statement;
	std::string value_alias;


	ValueQuery_Defunct() {
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

struct ValueQuery {
private:
	std::string query_statement;
	std::string value_alias;

	std::string associated_column_name;
	std::string raw_result_value;

	TableCellDisplayInfo operation_info;
	TableCellDisplayInfo argument_info;
	TableCellDisplayInfo result_info;

	bool value_locked;

public:
	ValueQuery(ValueOperation operation, ValueOperationArgument argument) {
		operation_info = TableCellDisplayInfo(operation.GetDisplayName(), operation.GetDisplayColor());
		argument_info = TableCellDisplayInfo(argument.display_name, argument.argument_color);
		result_info = TableCellDisplayInfo("NOT CALCULATED", DisplayColor());

		query_statement = operation.GenerateArgumentQuery(argument);
		value_alias = operation.GenerateArgumentAlias(argument);
		associated_column_name = argument.database_name;

		value_locked = false;
	}

	std::string GenerateQueryStatement(std::string table_name) {
		std::string complete_query = "(" + query_statement;
		complete_query = std::vformat(complete_query, std::make_format_args(table_name));
		complete_query += ") AS " + value_alias;
		return complete_query;
	}

	std::string GetAssociatedColumnName() const {
		return associated_column_name;
	}

	std::string GetRawResultValue() const {
		return raw_result_value;
	}

	TableCellDisplayInfo GetOperationDisplayInfo() {
		return operation_info;
	}

	TableCellDisplayInfo GetArgumentDisplayInfo() {
		return argument_info;
	}

	TableCellDisplayInfo GetResultDisplayInfo() {
		return result_info;
	}

	void SetRawResultValue(std::string raw_result_text) {
		raw_result_value = raw_result_text;
	}

	void UpdateResultDisplayInfo(std::string result_text, DisplayColor result_color) {
		result_info.SetText(result_text);
		result_info.SetColor(result_color);
	}

	bool IsLocked() const {
		return value_locked;
	}

	void SetLocked(bool updated_lock_state) {
		value_locked = updated_lock_state;
	}
};

} // namespace monster_calculator