#pragma once
#include <vector>

#include "mcc_value_structs.h"

namespace monster_calculator {

// value calculation enum values
extern const std::vector<ValueOperationArgument> kNumericalCalcArguments;

// value calculation types
extern const ValueOperation kAvgCalcOperation;
extern const ValueOperation kMinCalcOperation;
extern const ValueOperation kMaxCalcOperation;
extern const ValueOperation kSumCalcOperation;
extern const ValueOperation kModeCalcOperation;

} // namespace monster_calculator