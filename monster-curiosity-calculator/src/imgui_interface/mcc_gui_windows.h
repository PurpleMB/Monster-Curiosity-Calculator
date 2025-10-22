#pragma once

#include <vector>
#include <memory>

#include "../data_communication/mcc_parameter_structs.h"
#include "../data_communication/mcc_value_structs.h"
#include "../data_communication/mcc_communication_structs.h"

namespace purple_mb::monster_calculator {
	void DrawMenuBarWindow(OutputEnvironment& output_environment);

	void DrawSetParameterWindow(OutputEnvironment& output_environment, 
		std::vector<std::shared_ptr<ParameterType>> parameter_types, ParameterTypeConverter param_converter);

	void DrawDropdownParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter, float label_width, float combo_width);
	void DrawSliderParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter);
	void DrawButtonGridParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter);
	void DrawImageParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter, OutputEnvironment& output_environment,
		float label_width, float combo_width);

	void DrawOpenParameterSelector(OpenParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter, float label_width, float input_width);
	
	void DrawIntegerParameterSelector(IntegerParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter, float label_width, float input_width);
	void DrawDecimalParameterSelector(DecimalParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter, float label_width, float input_width);
	
	void DrawParameterGroupSelector(int& group_index, ParameterSet& parameter_set, float label_width, float combo_width);
	void DrawSubsetParameterTable(OutputEnvironment& output_environment);

	void DrawValueParameterWindow(OutputEnvironment& output_environment, std::vector<std::shared_ptr<ValueOperation>> value_operations, ParameterTypeConverter param_converter);
	void DrawValueOperationTable(OutputEnvironment& output_environment, ParameterTypeConverter param_converter);

	void DrawSetDisplayWindow(OutputEnvironment& output_environment, std::vector<ColumnStatus>& column_statuses);
	void DrawSubsetSizeTable(OutputEnvironment& output_environment, ParameterSet& param_set);

} // namespace purple_mb::monster_calculator
