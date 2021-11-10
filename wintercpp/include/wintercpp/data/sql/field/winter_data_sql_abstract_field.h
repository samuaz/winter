//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTERCPP_DATA_SQL_ABSTRACT_FIELD_H
#define WINTERCPP_DATA_SQL_ABSTRACT_FIELD_H

#include <wintercpp/data/sql/field/winter_data_sql_field_type.h>

#include <string>

namespace winter::data::sql_impl {

struct AbstractField {
  virtual const FieldType &type() const = 0;

  virtual const std::string &name() const = 0;

  virtual ~AbstractField() = default;
};
}  // namespace winter::data::sql_impl

#endif	// WINTERCPP_DATA_SQL_ABSTRACT_FIELD_H
