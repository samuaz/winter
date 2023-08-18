//
// Created by Samuel Azcona on 23/05/2020.
//
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_not_in.h>

using namespace winter::data::sql_impl;

NotIn::NotIn(const StatementValue& statement_value) :
    predicate_(statement_value) {}

NotIn::NotIn(const Predicate& predicate) :
    predicate_(predicate) {}

std::vector<PreparedStatementField> NotIn::Fields() const {
    return predicate_.fields();
};

std::string NotIn::Query() const {
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