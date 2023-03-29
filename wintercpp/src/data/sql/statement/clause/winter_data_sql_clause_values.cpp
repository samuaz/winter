//
// Created by Samuel Azcona on 07/06/2020.
//

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_abstract_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_values.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

winter::data::sql_impl::Values::Values(
    std::vector<std::shared_ptr<
        winter::data::sql_impl::AbstractPreparedStatementField> > fields) :
    Clause("($columns) VALUES ($set_values)", "$set_values"),
    _fields(std::move(fields)) {}

std::string winter::data::sql_impl::Values::Values::name() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to name function on clause"));
};

winter::data::sql_impl::FieldType winter::data::sql_impl::Values::fieldType() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to fieldtype function on clause"));
}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Values::Prepare() {
    std::vector<std::string> columns;
    for (const auto &field : _fields) { columns.push_back(field->name()); }

    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        "$columns",
        winter::data::sql_impl::CommaSeparatedValue(columns)));

    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        param(),
        winter::data::sql_impl::CommaSeparatedStatement(_fields)));

    return winter::data::sql_impl::PreparedStatement(
        StatementType::kClause, statement_template(), _fields);
}
