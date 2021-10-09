//
// Created by Samuel Azcona on 14/03/2020.
//

#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include "wintercpp/data/sql/column/winter_data_sql_column.h"

using namespace winter::data::sql;

Table::Table(std::string name, TableType table_type, DatabaseType database_type) : name_(std::move(name)),
										   type_(table_type),
										   database_type_(database_type) {}

Table::Table(std::string name, DatabaseType database_type) : name_(std::move(name)),
							     type_(TableType::kTable),
							     database_type_(database_type) {}

const std::string &
Table::name() const {
  return name_;
}

const std::set<Column, ColumnComparator> &
Table::columns() const {
  return columns_;
}

const Column &
Table::RegisterColumn(const Column &col) {
  columns_.insert(col);
  return *columns_.find(col);
}

const Column &
Table::String(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kString));
}

const Column &
Table::Int(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kInt));
}

const Column &
Table::Long(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kLong));
}

const Column &
Table::Float(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kFloat));
}

const Column &
Table::Double(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kDouble));
}

const Column &
Table::Boolean(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kBoolean));
}

const Column &
Table::Date(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kDate));
}

const Column &
Table::Enum(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kEnum));
}

const Column &
Table::Blob(const std::string &name) {
  return RegisterColumn(Column(
      *this,
      name,
      FieldType::kBlob));
}

Table::~Table() {}

TableType
Table::tableType() const {
  return type_;
}
