//
// Created by Samuel Azcona on 27/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_DELETE_H
#define WINTERCPP_WINTER_DATA_SQL_DELETE_H

#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>

#include <string>
#include <vector>

namespace winter::data::sql {

class Delete final : public virtual Statement<Delete> {
 public:
  Delete();

  using Statement<Delete>::prepared_statement;
  using Statement<Delete>::operator<<;

  ~Delete() override = default;

 protected:
  void BuildStatement() override;

 private:
  using Statement<Delete>::prepared_statement_;
  using Statement<Delete>::type_;
};

}  // namespace winter::data::sql

#endif	// WINTERCPP_WINTER_DATA_SQL_DELETE_H