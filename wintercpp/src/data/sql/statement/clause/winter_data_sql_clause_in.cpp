//
// Created by Samuel Azcona on 23/05/2020.
//
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_in.h>

using namespace winter::data::sql_impl;

In::In(const StatementValue& statement_value) :
    predicate_(statement_value) {}

In::In(const Predicate& predicate) :
    predicate_(predicate) {}

std::vector<PreparedStatementField> In::Fields() const {
    return predicate_.fields();
};

std::string In::Query() const {
    if (predicate_.has_fields()) {
        return winter::util::string::replace_value(
            query_template_,
            query_param_,
            CommaSeparatedParenthesesPlaceHolder(predicate_.fields().size()));
    }
    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        predicate_.lstatementStr());
}