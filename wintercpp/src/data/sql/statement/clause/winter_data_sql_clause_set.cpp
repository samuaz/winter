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

std::string winter::data::sql_impl::Set::Set::name() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to name function on clause"));
};

winter::data::sql_impl::FieldType winter::data::sql_impl::Set::fieldType() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to fieldtype function on clause"));
}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Set::Prepare() {
    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        param(),
        winter::data::sql_impl::commaSeparatedEqualValue(fields_)));
    return winter::data::sql_impl::PreparedStatement(
        StatementType::kClause, statement_template(), fields_);
}
