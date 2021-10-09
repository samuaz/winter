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

class Column {
 public:
  Column(Table &table, std::string column_name, FieldType column_type);

  Column(const Column &c1) : table_(c1.table_), name_(c1.name_), type_(c1.type_){};

  Column(const Column *c1) : table_(c1->table_), name_(c1->name_), type_(c1->type_){};

  const Table &table() const;

  const std::string &TableName() const;

  const std::string &name() const;

  const FieldType &type() const;

  const Column *
  operator->() const {
    return this;
  }

 protected:
  const Table &table_;
  std::string name_;
  FieldType type_;
};

struct ColumnComparator {
  bool
  operator()(const std::shared_ptr<Column> &lhs, const std::shared_ptr<Column> &rhs) const {
    std::stringstream s1, s2;
    s1 << lhs->TableName() << lhs->name();
    s2 << rhs->TableName() << rhs->name();
    return s1.str() < s2.str();
  }

  bool
  operator()(Column *lhs, Column *rhs) const {
    std::stringstream s1, s2;
    s1 << lhs->TableName() << lhs->name();
    s2 << rhs->TableName() << rhs->name();
    return s1.str() < s2.str();
  }

  bool
  operator()(const Column &lhs, const Column &rhs) const {
    std::stringstream s1, s2;
    s1 << lhs.TableName() << lhs.name();
    s2 << rhs.TableName() << rhs.name();
    return s1.str() < s2.str();
  }
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_COLUMN */
