//
// Created by Samuel Azcona on 18/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_parenthesis.h>

winter::data::sql::Parenthesis::Parenthesis(winter::data::sql::Clause *clause) : Clause("($clause)", "$clause") {
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$clause",
      clause->Prepare().statement_template()));
}

winter::data::sql::Parenthesis::Parenthesis(const std::string &clause) : Clause("($clause)", "$clause") {
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$clause",
      clause));
}

winter::data::sql::PreparedStatement
winter::data::sql::Parenthesis::Prepare() {
  return winter::data::sql::PreparedStatement(
      StatementType::kClause,
      statement_template());
}
