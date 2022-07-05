//
// Created by Samuel Azcona on 16/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_set.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <utility>

winter::data::sql_impl::Set::Set(
    std::vector<std::shared_ptr<
        winter::data::sql_impl::AbstractPreparedStatementField> > fields) :
    Clause("SET $fields", "$fields"),
    fields_(std::move(fields)) {}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Set::Prepare() {
    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        param(),
        winter::data::sql_impl::commaSeparatedEqualValue(fields_)));
    return winter::data::sql_impl::PreparedStatement(
        StatementType::kClause, statement_template(), fields_);
}
