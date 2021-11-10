//
// Created by Samuel Azcona on 16/03/2020.
//

#include <wintercpp/data/sql/table/winter_data_sql_id_type.h>

using namespace winter::data::sql_impl;

IDType
TypeId<int>::Get() {
  return IDType::INT;
}

IDType
TypeId<std::string>::Get() {
  return IDType::STRING;
}

IDType
TypeId<long>::Get() {
  return IDType::LONG;
}

IDType
TypeId<void>::Get() {
  return IDType::NONE;
}
