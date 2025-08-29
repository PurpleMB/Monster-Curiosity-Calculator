#pragma once

#include <vector>
#include <memory>

#include "mcc_parameter_structs.h"
#include "mcc_value_structs.h"
#include "mcc_communication_structs.h"

namespace monster_calculator {

	void BeginStyledWindow(WindowParameters& window_parameters);
	void EndStyledWindow(WindowParameters& window_parameters);
	void DrawWelcomeWindow(OutputEnvironment& output_environment);
	void DrawSetParameterWindow(OutputEnvironment& output_environment, 
		std::vector<std::shared_ptr<ParameterType>> parameter_types, ParameterTypeConverter param_converter);
	void DrawEnumeratorParameterSelector(EnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter);
	void DrawSliderParameterSelector(SliderEnumeratedParameterType& param_type, ParameterOperation& operation, int& selected_value_index, QueryParameter& building_parameter);
	void DrawOpenParameterSelector(OpenParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter);
	void DrawIntegerParameterSelector(IntegerParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter);
	void DrawDecimalParameterSelector(DecimalParameterType& param_type, ParameterOperation& operation, QueryParameter& building_parameter);
	void DrawSubsetParameterTable(OutputEnvironment& output_environment);
	void DrawValueParameterWindow(OutputEnvironment& output_environment, std::vector<std::shared_ptr<ValueOperation>> value_operations);
	void DrawValueOperationTable(OutputEnvironment& output_environment);
	void DrawSetDisplayWindow(OutputEnvironment& output_environment, std::vector<ColumnStatus>& column_statuses);
	void DrawOutputLogWindow(OutputEnvironment& output_environment);

} // namespace monster_calculator
