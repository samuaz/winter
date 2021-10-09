//
// Created by Samuel Azcona on 14/03/2020.
//

#ifndef WINTER_DATA_SQL_STATEMENT
#define WINTER_DATA_SQL_STATEMENT

#include <wintercpp/data/sql/column/winter_data_sql_column.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement_field.h>

#include <string>
#include <utility>

namespace winter::data::sql {

class IStatement {
 public:
  virtual StatementType type() = 0;

  virtual const PreparedStatement &prepared_statement() = 0;

  virtual std::string transaction_id() = 0;

  virtual void set_transaction_id(const std::string &id) = 0;

 protected:
  virtual void BuildStatement() = 0;
};

template <typename Children>
class Statement : public virtual IStatement {
 public:

  explicit Statement(std::string query);

  Statement(std::string statement_template, const StatementType &statement_type);

  Statement(const Statement &statement);

  StatementType
  type() override;

  std::string
  transaction_id() override;

  void
  set_transaction_id(const std::string &transaction_id);

  Children &
  set_statement_template(const std::string &statement_template);

  template <typename T>
  Children &
  Value(const T value);

  template <typename T>
  Children &
  Value(const Column &row, const T value);

  template <typename T>
  Children &
  Value(const Column &row, const T value, const std::string &custom_value);

  const PreparedStatement &
  prepared_statement() override;

  template <typename TRANSACTION>
  auto
  Execute(TRANSACTION &transaction);

  template <typename TRANSACTION>
  auto
  Execute(std::shared_ptr<TRANSACTION> &transaction);

  template <typename TRANSACTION>
  auto
  Execute(TRANSACTION *transaction);

  template <typename TRANSACTION>
  auto
  operator>>(TRANSACTION &transaction);

  template <typename TRANSACTION>
  auto
  operator>>(TRANSACTION *transaction);

  template <typename TRANSACTION>
  auto
  operator>>(std::shared_ptr<TRANSACTION> &transaction);

  template <typename CLAUSE>
  Children &
  AddClause(CLAUSE clause);

  template <typename CLAUSE>
  auto &
  operator<<(CLAUSE clause);

  virtual ~Statement();

 protected:
  std::string statement_template_;
  std::unique_ptr<PreparedStatement> prepared_statement_;
  StatementType type_{};

 private:
  std::string transaction_id_ = winter::random::uuid();
  Children &
  This();
};

template <typename Children>
Statement<Children>::~Statement() = default;

}  // namespace winter::data::sql

#include "winter_data_sql_statement.tpp"

#endif /* WINTER_DATA_SQL_STATEMENT */
