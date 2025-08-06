#pragma once
#include <vector> // used by ParameterValue lists

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// parameter values
extern const std::vector<ParameterValue> kTypeValuesList;
extern const std::vector<ParameterValue> kBinaryValuesList;
extern const std::vector<ParameterValue> kColorValuesList;

// enumerated parameters
extern const EnumeratedParameterType kPrimaryTypeParam;
extern const EnumeratedParameterType kIsBabyParam;
extern const EnumeratedParameterType kColorParam;

// numerical parameter operations and values
extern const std::vector<ParameterValue> kStandardNumericalOperations;

// numerical parameters
extern const NumericalParameterType kHealthParam;
extern const NumericalParameterType kStatTotalParam;

} //namespace monster_calculator