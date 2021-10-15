//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_TABLE
#define WINTER_DATA_SQL_TABLE

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/table/winter_data_sql_id_type.h>
#include <wintercpp/util/winter_random.h>

#include <any>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>

namespace winter::data::sql {

enum class TableType {
  kTable,
  kUUID,
  kLong,
  kInt
};

enum class DatabaseType {
  kGeneric,
  kMysql,
  KPostgresql
};

class Table;
struct TableComparator;

template <typename T>
class AutoGeneratedTable {
 public:
  virtual T GenerateId() const = 0;
};

class Table {
 public:
  Table(std::string name, TableType table_type, DatabaseType database_type);

  Table(std::string name, DatabaseType database_type);

  const std::string &name() const;

  //std::vector<Column> columns() const;

  const std::set<Column, ColumnComparator> &columns() const;

  TableType tableType() const;

  const Column &RegisterColumn(const Column &col);

  const Column &RegisterColumn(const std::string &name, FieldType fieldType);

  const Column &Char(const std::string &name);

  const Column &SignedChar(const std::string &name);

  const Column &UnsignedChar(const std::string &name);

  const Column &String(const std::string &name);

  const Column &Short(const std::string &name);

  const Column &UShort(const std::string &name);

  const Column &Int(const std::string &name);

  const Column &UInt(const std::string &name);

  const Column &Decimal(const std::string &name);

  const Column &BigInt(const std::string &name);

  const Column &Long(const std::string &name);

  const Column &ULong(const std::string &name);

  const Column &Float(const std::string &name);

  const Column &Double(const std::string &name);

  const Column &Boolean(const std::string &name);

  const Column &Date(const std::string &name);

  const Column &DateTime(const std::string &name);

  const Column &TimeStamp(const std::string &name);

  const Column &Enum(const std::string &name);

  const Column &Blob(const std::string &name);

  virtual ~Table();

 protected:
  const std::string name_;
  std::set<Column, ColumnComparator> columns_;
  const TableType type_;
  const DatabaseType database_type_;
  // std::map<std::string, Column> columns_;
};

struct TableComparator {
  bool
  operator()(const std::shared_ptr<Table> &lhs, const std::shared_ptr<Table> &rhs) const;

  bool
  operator()(Table *lhs, Table *rhs) const;

  bool
  operator()(const Table &lhs, const Table &rhs) const;
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_TABLE */
