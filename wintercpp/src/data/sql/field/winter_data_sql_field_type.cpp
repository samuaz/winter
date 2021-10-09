//
// Created by Samuel Azcona on 14/03/2020.
//

#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>

using namespace winter::data::sql;

FieldType
TypeField<uint8_t>::Get() {
  return FieldType::kUchar;
}

FieldType
TypeField<int8_t>::Get() {
  return FieldType::kSchar;
}

FieldType
TypeField<char>::Get() {
  return FieldType::kChar;
}

FieldType
TypeField<uint16_t>::Get() {
  return FieldType::kUshort;
}

FieldType
TypeField<int16_t>::Get() {
  return FieldType::KShort;
}

FieldType
TypeField<uint32_t>::Get() {
  return FieldType::KUint;
}

FieldType
TypeField<int32_t>::Get() {
  return FieldType::kInt;
}

FieldType
TypeField<uint64_t>::Get() {
  return FieldType::kUlong;
}

FieldType
TypeField<int64_t>::Get() {
  return FieldType::kLong;
}

FieldType
TypeField<std::string>::Get() {
  return FieldType::kString;
}

FieldType
TypeField<bool>::Get() {
  return FieldType::kBoolean;
}

FieldType
TypeField<char *>::Get() {
  return FieldType::kString;
}

FieldType
TypeField<char const *>::Get() {
  return FieldType::kString;
}

FieldType
TypeField<std::istream *>::Get() {
  return FieldType::kBlob;
}

FieldType
TypeField<Date>::Get() {
  return FieldType::kDate;
}

FieldType
TypeField<DateTime>::Get() {
  return FieldType::kDateTime;
}