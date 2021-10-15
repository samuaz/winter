//
// Created by Samuel Azcona on 07/06/2020.
//

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_abstract_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_values.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <deque>
winter::data::sql::Values::Values(
    std::deque<
	std::shared_ptr<winter::data::sql::AbstractPreparedStatementField> >
	fields) :
    Clause("($columns) VALUES ($set_values)", "$set_values"),
    _fields(std::move(fields)) {}

winter::data::sql::PreparedStatement
winter::data::sql::Values::Prepare() {
  std::vector<std::string> columns;
  for (const auto &field : _fields) {
    columns.push_back(field->name());
  }

  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      "$columns",
      winter::data::sql::CommaSeparatedValue(columns)));

  set_statement_template(winter::util::string::replace_value(
      statement_template(),
      param(),
      winter::data::sql::CommaSeparatedStatement(_fields)));

  return winter::data::sql::PreparedStatement(
      StatementType::kClause,
      statement_template(),
      _fields);
}
