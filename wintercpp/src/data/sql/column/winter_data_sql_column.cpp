//
// Created by Samuel Azcona on 14/03/2020.
//

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <utility>

using namespace winter::data::sql;

Column::Column(Table &table, std::string column_name, FieldType column_type) : table_(std::move(table)),
									       name_(std::move(column_name)),
									       type_(column_type) {}

const std::string &
Column::name() const {
  return name_;
}

const FieldType &
Column::type() const {
  return type_;
}

const Table &
Column::table() const {
  return table_;
}

const std::string &
Column::TableName() const {
  return table_.name();
}

bool ColumnComparator::operator()(const std::shared_ptr<Column> &lhs, const std::shared_ptr<Column> &rhs) const {
  std::stringstream s1, s2;
  s1 << lhs->TableName() << lhs->name();
  s2 << rhs->TableName() << rhs->name();
  return s1.str() < s2.str();
}

bool ColumnComparator::operator()(Column *lhs, Column *rhs) const {
  std::stringstream s1, s2;
  s1 << lhs->TableName() << lhs->name();
  s2 << rhs->TableName() << rhs->name();
  return s1.str() < s2.str();
}

bool ColumnComparator::operator()(const Column &lhs, const Column &rhs) const {
  std::stringstream s1, s2;
  s1 << lhs.TableName() << lhs.name();
  s2 << rhs.TableName() << rhs.name();
  return s1.str() < s2.str();
}