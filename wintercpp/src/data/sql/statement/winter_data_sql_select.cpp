//
// Created by Samuel Azcona on 27/03/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <vector>

using namespace winter::data::sql;

Select::Select(const std::string &query) : Statement<Select>(query, StatementType::kSelect) {}

Select::Select() : Statement<Select>("SELECT $columns", StatementType::kSelect) {}

Select::Select(std::vector<Column> columns) : Statement("SELECT $columns", StatementType::kSelect), columns_(std::move(columns)) {}

void Select::writeColumns() {
  if (columns_.empty()) {
    winter::util::string::replace(statement_template_, "$columns", "*");
    return;
  }

  std::vector<std::string> columns;
  for (auto const &col : columns_) {
    columns.push_back(col->TableName() + "." + col->name());
  }
  winter::util::string::replace(
      statement_template_,
      "$columns",
      CommaSeparatedValue(columns));
  prepared_statement_->columns(columns_);
}

Select &
Select::operator<<(std::vector<Column> columns) {
  columns_ = std::move(columns);
  return *this;
}

void Select::BuildStatement() {
  writeColumns();
  prepared_statement_->set_statement_template(statement_template_);
}
