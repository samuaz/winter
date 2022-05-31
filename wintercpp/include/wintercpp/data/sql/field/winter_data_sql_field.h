//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_FIELD
#define WINTER_DATA_SQL_FIELD

#include <wintercpp/data/sql/field/winter_data_sql_abstract_field.h>
#include <wintercpp/data/sql/field/winter_data_sql_data_type.h>

namespace winter::data::sql_impl {

template <typename T>
class Field : public virtual AbstractField {
 public:
  explicit Field(T value) :
      value_(std::move(value)),
      type_(TypeField<T>::Get()) {}

  Field(std::string name, T value) :
      name_(std::move(name)),
      value_(std::move(value)),
      type_(TypeField<T>::Get()) {}

  Field(const Field &field) :
      value_(field.value_),
      type_(field.type_),
      name_(field.name_) {}

  explicit Field(const Field *field) :
      value_(field->value_),
      type_(field->type_),
      name_(field->name_) {}

  const T &value() const;

  const FieldType &type() const override;

  const std::string &name() const override;

  void value(T value);

  ~Field() override = default;

 protected:
  T value_;
  FieldType type_;
  std::string name_;
};

}  // namespace winter::data::sql_impl

#include "winter_data_sql_field.tpp"

#endif /* WINTER_DATA_SQL_FIELD */
