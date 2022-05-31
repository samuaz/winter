//
// Created by Samuel Azcona on 13/04/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_UPDATE_H
#define WINTERCPP_WINTER_DATA_SQL_UPDATE_H

#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>
#include <wintercpp/util/winter_string_util.h>

#include <memory>
#include <string>

namespace winter::data::sql_impl {

class Update : public virtual Statement<Update> {
 public:
  explicit Update(const std::string &query);

  explicit Update(std::shared_ptr<Table> table);

  using Statement<Update>::prepared_statement;

  ~Update() override = default;

 protected:
  void BuildStatement() override;

 private:
  using Statement<Update>::prepared_statement_;
  using Statement<Update>::type_;
  const std::shared_ptr<Table> table_;
};
}  // namespace winter::data::sql_impl

#endif	// WINTERCPP_WINTER_DATA_SQL_UPDATE_H