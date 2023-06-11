//
// Created by Samuel Azcona on 18/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_parenthesis.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>

#include "wintercpp/data/sql/statement/winter_data_sql_statement_values.h"

winter::data::sql_impl::Parenthesis::Parenthesis(
    const winter::data::sql_impl::StatementValue& statement_value) :
    statement_value_(statement_value) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::Parenthesis::Fields() const {
    return {};
};

std::string
winter::data::sql_impl::Parenthesis::Query() const {
    auto clauseQuery = [&]() -> std::string {
        if (auto clause = std::get_if<std::shared_ptr<Clause>>(&statement_value_)) {
            return clause->get()->Query();
        }
        std::string typeName = StatementValueType(statement_value_.index());
        std::string error = "invalid statement_value " + typeName + "not supported";
        throw ::winter::exception::WinterInternalException::Create(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            (error));
    };

    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        clauseQuery());
}
