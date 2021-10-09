//
// Created by Samuel Azcona on 27/03/2020.
//

#include <wintercpp/data/sql/statement/winter_data_sql_select.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_util.h>
#include <wintercpp/util/winter_string_util.h>

#include <vector>

using namespace winter::data::sql;

Select::Select(const std::string &query) : Statement<Select>(query, StatementType::kSelect) {}

Select::Select() : Statement<Select>("SELECT $columns", StatementType::kSelect) {
  winter::util::string::replace(statement_template_, "$columns", "*");
}

Select::Select(std::set<Column, ColumnComparator> columns) : Statement("SELECT $columns", StatementType::kSelect),
							     columns_(std::move(columns)) {
  writeColumns();
}

void Select::writeColumns() {
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
Select::operator<<(std::set<Column, ColumnComparator> columns) {
  columns_ = std::move(columns);
  writeColumns();
  return *this;
}

void Select::BuildStatement() {
  prepared_statement_->set_statement_template(statement_template_);
}
