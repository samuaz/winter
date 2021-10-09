//
// Created by Samuel Azcona on 14/03/2020.
//

#include <wintercpp/data/sql/table/winter_data_sql_uuid_table.h>

using namespace winter::data::sql;

UUIDTable::UUIDTable(const std::string &name, bool binary, DatabaseType database_type) : Table(name, TableType::kUUID, database_type),
											 id_(RegisterColumn(Column(*this, "id", FieldType::kString))),
											 binary_(binary) {}

std::string
UUIDTable::GenerateId() const {
  if (binary_) {
    return winter::random::uuidNoDashed();
  }
  return winter::random::uuidDashed();
}

bool UUIDTable::binary() const {
  return binary_;
}

const Column &
UUIDTable::id() const {
  return id_;
}
