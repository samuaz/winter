//
// Created by Samuel Azcona on 07/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_into.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

winter::data::sql::Into::Into(std::shared_ptr<Table> table) :
    Clause("INTO $table", "$table"),
    table_(std::move(table)) {}

winter::data::sql::PreparedStatement
winter::data::sql::Into::Prepare() {
  GenerateStatement();
  return winter::data::sql::PreparedStatement(
      StatementType::kClause,
      statement_template());
}

void winter::data::sql::Into::GenerateStatement() {
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      param(),
      winter::data::sql::CommaSeparatedValue({table_->name()})));
}