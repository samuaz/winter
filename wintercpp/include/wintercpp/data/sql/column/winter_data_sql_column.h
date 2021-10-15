//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_COLUMN
#define WINTER_DATA_SQL_COLUMN

#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>

#include <any>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace winter::data::sql {

class Table;
class Column;
struct ColumnComparator;

class Column final {
 public:
  Column(Table &table, std::string column_name, FieldType column_type);

  Column(const Column &column) :
      table_(column.table_),
      name_(column.name_),
      type_(column.type_){};

  Column(const Column *column) :
      table_(column->table_),
      name_(column->name_),
      type_(column->type_){};

  bool operator==(const Column &column) const;

  const Table &table() const;

  const std::string &TableName() const;

  const std::string &name() const;

  const FieldType &type() const;

  const Column *
  operator->() const {
    return this;
  }

 private:
  const Table &table_;
  const std::string name_;
  const FieldType type_;
};

struct ColumnComparator {
  bool
  operator()(const std::shared_ptr<Column> &lhs, const std::shared_ptr<Column> &rhs) const;

  bool
  operator()(Column *lhs, Column *rhs) const;

  bool
  operator()(const Column &lhs, const Column &rhs) const;
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_COLUMN */
