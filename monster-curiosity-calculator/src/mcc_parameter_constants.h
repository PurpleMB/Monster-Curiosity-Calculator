#pragma once
#include <vector> // used by ParameterValue lists

#include "mcc_parameter_structs.h"

namespace monster_calculator {

// parameter values
extern const std::vector<ParameterValue> kTypeValuesList;
extern const std::vector<ParameterValue> kBinaryValuesList;
extern const std::vector<ParameterValue> kColorValuesList;
extern const std::vector<ParameterValue> kShapeValuesList;
extern const std::vector<ParameterValue> kEggGroupValuesList;

// enumerated parameters
extern const EnumeratedParameterType kPrimaryTypeParam;
extern const EnumeratedParameterType kEitherTypeParam;
extern const EnumeratedParameterType kIsDefaultParam;
extern const EnumeratedParameterType kIsBabyParam;
extern const EnumeratedParameterType kColorParam;
extern const EnumeratedParameterType kShapeParam;
extern const EnumeratedParameterType kPrimaryEggParam;

// numerical parameter operations and values
extern const std::vector<ParameterValue> kStandardNumericalOperations;

// numerical parameters
extern const NumericalParameterType kDexNumParam;
extern const NumericalParameterType kCatchRateParam;
extern const NumericalParameterType kHealthParam;
extern const NumericalParameterType kStatTotalParam;

} //namespace monster_calculator