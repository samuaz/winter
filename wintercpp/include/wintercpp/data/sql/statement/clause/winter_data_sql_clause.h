//
// Created by Samuel Azcona on 23/05/2020.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_CLAUSE_H
#define WINTERCPP_WINTER_DATA_SQL_CLAUSE_H

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>

#include <string>

namespace winter::data::sql {

class Clause {
 public:
  Clause &operator<<(const std::string &rvalue);

  const std::string &query() const;

  std::string param();

  std::string statement_template();

  virtual PreparedStatement Prepare() = 0;

 protected:
  Clause &BuildQuery();
  Clause(std::string statement_template, std::string param);
  void set_statement_template(const std::string &statement_template);

 private:
  std::string statement_template_{};
  const std::string param_{};
  std::string query_{};
};

}  // namespace winter::data::sql

#endif	// WINTERCPP_WINTER_DATA_SQL_CLAUSE_H
