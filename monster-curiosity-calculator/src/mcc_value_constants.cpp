#pragma once
#include <vector>

#include "mcc_value_structs.h"
#include "mcc_value_constants.h"

namespace monster_calculator {

// value calculation enum values
extern const std::vector<ValueOperationArgument> kNumericalCalcArguments = {
    ValueOperationArgument("Health",	        "hp",	            kRedColor),
    ValueOperationArgument("Attack",	        "attack",	        kGreenColor),
    ValueOperationArgument("Defense",	        "defense",	        kBlueColor),
    ValueOperationArgument("Special Attack",	"special_attack",	kOrangeColor),
    ValueOperationArgument("Special Defense",	"special_defense",	kPurpleColor),
    ValueOperationArgument("Speed",	            "speed",	        kPinkColor),
    ValueOperationArgument("Stat Total",	    "stat_total",	    kGrayColor),
    ValueOperationArgument("Base Experience",	"base_experience",	kLinenColor),
    ValueOperationArgument("Base Happiness",	"base_happiness",	kRaspberryColor),
    ValueOperationArgument("Catch Rate",	    "catch_rate",	    kBrassColor),
    ValueOperationArgument("Hatch Cycles",	    "hatch_counter",	kCeladonColor),
    ValueOperationArgument("Height",	        "height",	        kSaffronColor),
    ValueOperationArgument("Weight",	        "weight",	        kFuschiaColor)
};

const std::string kAvgCalcDisplayName = "Subset Average";
const std::string kAvgCalcSelectFormat = "avg({0})";
const std::string kAvgCalcGroupFormat = "";
const std::string kAvgCalcOrderFormat = "";
const std::string kAvgCalcAliasFormat = "avg_{0}";
extern const ValueOperation kAvgCalcOperation = ValueOperation(
    kAvgCalcDisplayName,
    kAvgCalcSelectFormat,
    kAvgCalcGroupFormat,
    kAvgCalcOrderFormat,
    kAvgCalcAliasFormat,
    kRedColor,
    kNumericalCalcArguments
);

const std::string kMinCalcDisplayName = "Subset Minimum";
const std::string kMinCalcSelectFormat = "min({0})";
const std::string kMinCalcGroupFormat = "";
const std::string kMinCalcOrderFormat = "";
const std::string kMinCalcAliasFormat = "min_{0}";
extern const ValueOperation kMinCalcOperation = ValueOperation(
    kMinCalcDisplayName,
    kMinCalcSelectFormat,
    kMinCalcGroupFormat,
    kMinCalcOrderFormat,
    kMinCalcAliasFormat,
    kGreenColor,
    kNumericalCalcArguments
);

const std::string kMaxCalcDisplayName = "Subset Maximum";
const std::string kMaxCalcSelectFormat = "max({0})";
const std::string kMaxCalcGroupFormat = "";
const std::string kMaxCalcOrderFormat = "";
const std::string kMaxCalcAliasFormat = "max_{0}";
extern const ValueOperation kMaxCalcOperation = ValueOperation(
    kMaxCalcDisplayName,
    kMaxCalcSelectFormat,
    kMaxCalcGroupFormat,
    kMaxCalcOrderFormat,
    kMaxCalcAliasFormat,
    kBlueColor,
    kNumericalCalcArguments
);

const std::string kSumCalcDisplayName = "Subset Sum";
const std::string kSumCalcSelectFormat = "sum({0})";
const std::string kSumCalcGroupFormat = "";
const std::string kSumCalcOrderFormat = "";
const std::string kSumCalcAliasFormat = "sum_{0}";
extern const ValueOperation kSumCalcOperation = ValueOperation(
    kSumCalcDisplayName,
    kSumCalcSelectFormat,
    kSumCalcGroupFormat,
    kSumCalcOrderFormat,
    kSumCalcAliasFormat,
    kYellowColor,
    kNumericalCalcArguments
);

} // namespace monster_calculator