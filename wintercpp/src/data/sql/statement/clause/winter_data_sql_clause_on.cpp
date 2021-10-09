//
// Created by Samuel Azcona on 17/06/2020.
//

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_on.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

winter::data::sql::On::On(
    const winter::data::sql::Column &l_column,
    winter::data::sql::Condition condition,
    const winter::data::sql::Column &r_column) : Clause("ON $lcolumn $condition $rcolumn", "$lcolumn $condition $rcolumn") {
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$lcolumn",
      l_column->TableName() + Dot() + l_column->name()));
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$condition",
      sql::condition(condition)));
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$rcolumn",
      r_column->TableName() + Dot() + r_column->name()));
}

winter::data::sql::On::On(
    const winter::data::sql::Column &l_column,
    winter::data::sql::Condition condition) : Clause("ON $lcolumn $condition", "$lcolumn $condition") {
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$lcolumn",
      l_column->TableName() + Dot() + l_column->name()));
  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$condition",
      sql::condition(condition)));
}

winter::data::sql::PreparedStatement
winter::data::sql::On::Prepare() {
  return winter::data::sql::PreparedStatement(
      StatementType::kClause,
      statement_template());
}
