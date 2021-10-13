//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_FIELD_TYPE
#define WINTER_DATA_SQL_FIELD_TYPE

#include <string>

namespace winter::data::sql {

struct Date {
  std::string value;
};

struct DateTime {
  std::string value;
};

enum class FieldType : int {
  kNull,
  kUchar,
  kSchar,
  kChar,
  kString,
  kUshort,
  KShort,
  KUint,
  kInt,
  kBigInt,
  kUlong,
  kLong,
  KDecimal,
  kFloat,
  kDouble,
  kBoolean,
  kDate,
  kDateTime,
  kTimeStamp,
  kEnum,
  kBlob
};

template <typename T>
struct TypeField {
  static FieldType Get();
};

template <>
struct TypeField<uint8_t> {
  static FieldType Get();
};

template <>
struct TypeField<int8_t> {
  static FieldType Get();
};

template <>
struct TypeField<uint16_t> {
  static FieldType Get();
};

template <>
struct TypeField<int16_t> {
  static FieldType Get();
};

template <>
struct TypeField<uint32_t> {
  static FieldType Get();
};

template <>
struct TypeField<int32_t> {
  static FieldType Get();
};

template <>
struct TypeField<uint64_t> {
  static FieldType Get();
};

template <>
struct TypeField<int64_t> {
  static FieldType Get();
};

template <>
struct TypeField<double> {
  static FieldType Get();
};

template <>
struct TypeField<float> {
  static FieldType Get();
};

template <>
struct TypeField<bool> {
  static FieldType Get();
};

template <>
struct TypeField<std::string> {
  static FieldType Get();
};

template <>
struct TypeField<char> {
  static FieldType Get();
};

template <>
struct TypeField<char *> {
  static FieldType Get();
};

template <>
struct TypeField<const char *> {
  static FieldType Get();
};

template <>
struct TypeField<std::istream *> {
  static FieldType Get();
};

template <>
struct TypeField<Date> {
  static FieldType Get();
};

template <>
struct TypeField<DateTime> {
  static FieldType Get();
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_FIELD_TYPE */
