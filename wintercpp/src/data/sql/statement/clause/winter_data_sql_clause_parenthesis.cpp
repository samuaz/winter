//
// Created by Samuel Azcona on 18/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_parenthesis.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_values_utils.h>
#include <wintercpp/exception/generic/winter_exception.h>
#include <wintercpp/exception/generic/winter_internal_exception.h>

#include "wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h"

winter::data::sql_impl::Parenthesis::Parenthesis(
    const winter::data::sql_impl::StatementValue& statement_value) :
    predicate_(statement_value) {}

std::vector<std::shared_ptr<winter::data::sql_impl::AbstractPreparedStatementField>> winter::data::sql_impl::Parenthesis::Fields() const {
    return predicate_.fields();
};

std::string
winter::data::sql_impl::Parenthesis::Query() const {
    return winter::util::string::replace_value(
        query_template_,
        query_param_,
        predicate_.lstatementStr());
}
