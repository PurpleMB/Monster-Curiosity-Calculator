#pragma once

#include <vector>
#include <memory>

#include "mcc_parameter_structs.h"
#include "mcc_value_structs.h"
#include "mcc_communication_structs.h"

namespace monster_calculator {
	void DrawMenuBarWindow(OutputEnvironment& output_environment);

	void DrawSetParameterWindow(OutputEnvironment& output_environment, 
		std::vector<std::shared_ptr<ParameterType>> parameter_types, ParameterTypeConverter param_converter);

	void DrawDropdownParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter);
	void DrawSliderParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter);
	void DrawButtonGridParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter);
	void DrawImageButtonGridParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter, OutputEnvironment& output_environment);

	void DrawOpenParameterSelector(OpenParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter);
	
	void DrawIntegerParameterSelector(IntegerParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter);
	void DrawDecimalParameterSelector(DecimalParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter);
	
	void DrawParameterGroupSelector(int& parameter_group_index, std::vector<std::string> parameter_group_names_list);
	void DrawSubsetParameterTable(OutputEnvironment& output_environment);

	void DrawValueParameterWindow(OutputEnvironment& output_environment, std::vector<std::shared_ptr<ValueOperation>> value_operations, ParameterTypeConverter param_converter);
	void DrawValueOperationTable(OutputEnvironment& output_environment, ParameterTypeConverter param_converter);

	void DrawSetDisplayWindow(OutputEnvironment& output_environment, std::vector<ColumnStatus>& column_statuses);

} // namespace monster_calculator
