//
// Created by Samuel Azcona on 07/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_into.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

winter::data::sql_impl::Into::Into(std::shared_ptr<Table> table) :
    Clause("INTO $table", "$table"), table_(std::move(table)) {}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Into::Prepare() {
    GenerateStatement();
    return winter::data::sql_impl::PreparedStatement(StatementType::kClause,
                                                     statement_template());
}

std::string winter::data::sql_impl::Into::Into::name() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to name function on clause"));
};

winter::data::sql_impl::FieldType winter::data::sql_impl::Into::fieldType() {
    throw exception::WinterInternalException::Create(
        __FILE__,
        __FUNCTION__,
        __LINE__,
        ("invalid call to fieldtype function on clause"));
}

void winter::data::sql_impl::Into::GenerateStatement() {
    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        param(),
        winter::data::sql_impl::CommaSeparatedValue({table_->name()})));
}