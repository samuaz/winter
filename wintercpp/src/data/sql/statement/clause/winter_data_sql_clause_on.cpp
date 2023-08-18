//
// Created by Samuel Azcona on 17/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_on.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>
#include <wintercpp/util/winter_string_util.h>

#include <string>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"
#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

using namespace winter::data::sql_impl;
using namespace winter::util::string;

On::On(const StatementValue &l_statement_value,
       Condition             condition,
       const StatementValue &r_statement_value) :
    predicate_(l_statement_value, condition, r_statement_value) {}

On::On(const StatementValue &l_statement_value,
       Condition             condition) :
    predicate_(l_statement_value, condition) {}

std::vector<PreparedStatementField> On::Fields() const {
    return predicate_.fields();
};

std::string
On::Query() const {
    std::string result = winter::util::string::replace_value(
        query_template_,
        query_param_l,
        predicate_.lstatementStr());

    result = winter::util::string::replace_value(
        result,
        query_param_r,
        predicate_.rstatementStr());

    std::string query = replace_value(result, query_param_condition, predicate_.conditionStr());
    trim_string(query);
    return query;
}
