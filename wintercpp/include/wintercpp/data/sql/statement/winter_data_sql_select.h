//
// Created by Samuel Azcona on 27/03/2020.
//

#ifndef WINTER_DATA_SQL_SELECT
#define WINTER_DATA_SQL_SELECT

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <set>
#include <string>

namespace winter::data::sql {

class Select : public virtual Statement<Select> {
 public:
  Select();

  explicit Select(std::set<Column, ColumnComparator> columns);

  explicit Select(const std::string &query);

  Select &operator<<(std::set<Column, ColumnComparator> columns);

  using Statement<Select>::prepared_statement;
  using Statement<Select>::operator<<;

  ~Select() override = default;

 protected:
  void BuildStatement() override;

 private:
  using Statement<Select>::prepared_statement_;
  using Statement<Select>::type_;
  std::set<Column, ColumnComparator> columns_;
  std::vector<std::shared_ptr<Table> > tables_;

  void writeColumns();
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_SELECT */
