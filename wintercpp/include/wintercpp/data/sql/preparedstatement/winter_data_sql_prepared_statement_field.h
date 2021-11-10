//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTERCPP_DATA_SQL_PREPARED_STATEMENT_FIELD_H
#define WINTERCPP_DATA_SQL_PREPARED_STATEMENT_FIELD_H

#include <memory>
#include <string>

#include "../field/winter_data_sql_field.h"
#include "winter_data_sql_abstract_prepared_statement_field.h"

namespace winter::data::sql_impl {

template <typename T>
class PreparedStatementField : public virtual Field<T>,
			       public virtual AbstractPreparedStatementField {
 public:
  explicit PreparedStatementField(const T &value) :
      Field<T>(value) {}

  PreparedStatementField(const std::string &name, const T &value) :
      Field<T>(name, value) {}

  PreparedStatementField(
      const std::string &name,
      const T &value,
      std::string custom_value) :
      Field<T>(name, value),
      custom_value_(std::move(custom_value)) {}

  PreparedStatementField(const PreparedStatementField<T> &field) :
      Field<T>(field),
      custom_value_(field.custom_value_) {}

  explicit PreparedStatementField(const PreparedStatementField<T> *field) :
      Field<T>(field),
      custom_value_(field->custom_value_) {}

  const std::string &
  custom_value() const override {
    return custom_value_;
  }

  void
  set_custom_value(const std::string &custom_value) {
    PreparedStatementField::custom_value_ = custom_value;
  }

  bool
  IsCustomValue() override {
    return !custom_value_.empty();
  }

 private:
  std::string custom_value_;
};

template <typename T>
using QUERY_FIELD = std::shared_ptr<PreparedStatementField<T> >;

}  // namespace winter::data::sql_impl

#endif	// WINTERCPP_DATA_SQL_PREPARED_STATEMENT_FIELD_H
