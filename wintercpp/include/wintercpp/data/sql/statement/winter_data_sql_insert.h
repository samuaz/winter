//
// Created by Samuel Azcona on 16/03/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_INSERT_H
#define WINTERCPP_WINTER_DATA_SQL_INSERT_H

#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/table/winter_data_sql_id_type.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <string>

namespace winter::data::sql {

class Insert : public virtual Statement<Insert> {
 public:
  Insert();

  explicit Insert(const std::string &query);

  explicit Insert(std::shared_ptr<Table> table);

  using Statement<Insert>::prepared_statement;
  /*
        template<typename T>
        Insert &setId(const std::string &idAttributeName, const T &value, const
        std::string &custom_value);

        template<typename T>
        Insert &setId(const std::string &idAttributeName, const T &value);
      */
  // void GenerateId();

  ~Insert() override = default;

 protected:
  void BuildStatement() override;

 private:
  using Statement<Insert>::prepared_statement_;
  using Statement<Insert>::type_;
  std::shared_ptr<Table> table_;
};
}  // namespace winter::data::sql

#endif	// WINTERCPP_WINTER_DATA_SQL_INSERT_H
