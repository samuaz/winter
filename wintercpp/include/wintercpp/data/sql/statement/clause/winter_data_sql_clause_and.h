//
// Created by Samuel Azcona on 21/05/2020.
//

#ifndef WINTER_DATA_SQL_CLAUSE_AND
#define WINTER_DATA_SQL_CLAUSE_AND

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_operator.h>
#include <wintercpp/data/sql/statement/clause/winter_data_sql_clause_predicate.h>

#include <queue>

namespace winter::data::sql {

class And : public virtual Clause {
 public:
  explicit And(const Predicate &predicate);

  explicit And(Column column);

  explicit And(Column column, Condition);

  PreparedStatement Prepare() override;

  template <typename T>
  static Predicate
  MakePredicate(const Column &column, Condition condition, T value) {
    return Predicate(
	column,
	std::make_shared<PreparedStatementField<T> >(
	    column->name(),
	    value),
	condition);
  }

  template <typename T>
  static Predicate
  MakePredicate(
      const Column &column,
      Condition condition,
      T value,
      const std::string &custom_value) {
    return Predicate(
	column,
	std::make_shared<PreparedStatementField<T> >(
	    column->name(),
	    value,
	    custom_value),
	condition);
  }

 private:
  Column column_;
  std::shared_ptr<AbstractPreparedStatementField> field_;
  Condition condition_{};
  bool is_predicate_ = false;
};

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_CLAUSE_AND */
