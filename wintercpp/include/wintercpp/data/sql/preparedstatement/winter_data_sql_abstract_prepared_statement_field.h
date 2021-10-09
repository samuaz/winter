//
// Created by Samuel Azcona on 15/04/2020.
//

#ifndef WINTER_DATA_SQL_ABSTRACT_PREPARED_STATEMENT_FIELD
#define WINTER_DATA_SQL_ABSTRACT_PREPARED_STATEMENT_FIELD

#include <wintercpp/data/sql/field/winter_data_sql_abstract_field.h>

namespace winter::data::sql {
struct AbstractPreparedStatementField : public virtual AbstractField {
  virtual const std::string &custom_value() const = 0;

  virtual bool IsCustomValue() = 0;
};
}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_ABSTRACT_PREPARED_STATEMENT_FIELD */
