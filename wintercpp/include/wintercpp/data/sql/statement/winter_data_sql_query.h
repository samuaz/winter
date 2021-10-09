//
// Created by Samuel Azcona on 21/09/2020.
//

#ifndef WINTER_DATA_SQL_QUERY
#define WINTER_DATA_SQL_QUERY

#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_from.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_where.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>
#include <wintercpp/data/sql/table/winter_data_sql_table.h>

#include <string>
#include <vector>

namespace winter::data::sql {

class Query : public virtual Statement<Query> {
 public:
  explicit Query(StatementType statement_type, const std::string &query) : Statement<Query>(query, statement_type) {}

  ~Query() override = default;

 protected:
  void
  BuildStatement() override {
    prepared_statement_->set_statement_template(statement_template_);
  }

 private:
  using Statement<Query>::prepared_statement_;
  using Statement<Query>::type_;
};

}  // namespace winter::data::sql
#endif /* WINTER_DATA_SQL_QUERY */
