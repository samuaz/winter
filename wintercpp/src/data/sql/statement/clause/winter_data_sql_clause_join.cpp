//
// Created by Samuel Azcona on 16/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_join.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

winter::data::sql_impl::Join::Join(std::shared_ptr<Table> table,
                                   JoinType type) :
    Clause("$type JOIN $table", "$table"),
    table_(std::move(table)), type_(type) {
    set_statement_template(winter::util::string::replace_value(
        statement_template(), "$type", GenerateType()));
    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        param(),
        winter::data::sql_impl::CommaSeparatedValue({table_->name()})));
}

winter::data::sql_impl::Join::Join(std::shared_ptr<Table> table) :
    Clause("JOIN $table", "$table"), table_(std::move(table)),
    type_(JoinType::DEFAULT) {
    set_statement_template(winter::util::string::replace_value(
        statement_template(),
        param(),
        winter::data::sql_impl::CommaSeparatedValue({table_->name()})));
}

winter::data::sql_impl::PreparedStatement
winter::data::sql_impl::Join::Prepare() {
    GenerateStatement();
    return winter::data::sql_impl::PreparedStatement(StatementType::kClause,
                                                     statement_template());
}

void winter::data::sql_impl::Join::GenerateStatement() {}

std::string winter::data::sql_impl::Join::GenerateType() {
    switch (type_) {
        case JoinType::INNER: return "INNER";
        case JoinType::LEFT: return "LEFT";
        case JoinType::RIGHT: return "RIGHT";
        case JoinType::CROSS: return "CROSS";
        case JoinType::DEFAULT: return "INNER";
    }
    return std::string();
}
