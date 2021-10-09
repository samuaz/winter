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
  explicit Statement(std::string query) : statement_template_(std::move(query)),
					  type_(StatementType::kNative) {}

  Statement(
      std::string statement_template,
      const StatementType &statement_type) : statement_template_(std::move(statement_template)),
					     type_(statement_type) {
    prepared_statement_ = std::make_unique<PreparedStatement>(type_, "", transaction_id_);
  }

  Statement(const Statement &statement) : transaction_id_(statement.transaction_id_),
					  statement_template_(statement.statement_template_),
					  prepared_statement_(
					      new PreparedStatement(*statement.prepared_statement_)),
					  type_(statement.type_) {}

  StatementType
  type() override {
    return type_;
  }

  std::string
  transaction_id() override {
    return transaction_id_;
  }

  void
  set_transaction_id(const std::string &transaction_id) override {
    transaction_id_ = transaction_id;
    prepared_statement_->set_id(transaction_id);
  };

  Children &
  set_statement_template(const std::string &statement_template) {
    prepared_statement_->set_statement_template(statement_template);
    return This();
  };

  template <typename T>
  Children &
  Value(const T value) {
    prepared_statement_->AddValue(new PreparedStatementField<T>(value));
    return This();
  };

  template <typename T>
  Children &
  Value(const Column &row, const T value) {
    prepared_statement_->AddValue(
	new PreparedStatementField<T>(row->name(), value));
    return This();
  };

  template <typename T>
  Children &
  Value(const Column &row, const T value, const std::string &custom_value) {
    prepared_statement_->AddValue(
	new PreparedStatementField<T>(row->name(), value, custom_value));
    return This();
  };

  const PreparedStatement &
  prepared_statement() override {
    BuildStatement();
    return *prepared_statement_;
  };

  template <typename TRANSACTION>
  auto
  Execute(TRANSACTION &transaction) {
    return transaction.Execute(This());
  }

  template <typename TRANSACTION>
  auto
  Execute(std::shared_ptr<TRANSACTION> &transaction) {
    return transaction->Execute(This());
  }

  template <typename TRANSACTION>
  auto
  Execute(TRANSACTION *transaction) {
    return transaction->Execute(This());
  }

  template <typename TRANSACTION>
  auto
  operator>>(TRANSACTION &transaction) {
    return Execute(transaction);
  }

  template <typename TRANSACTION>
  auto
  operator>>(TRANSACTION *transaction) {
    return Execute(transaction);
  }

  template <typename TRANSACTION>
  auto
  operator>>(std::shared_ptr<TRANSACTION> &transaction) {
    return Execute(transaction);
  }

  template <typename CLAUSE>
  Children &
  AddClause(CLAUSE clause) {
    auto preparedStatement = clause.Prepare();
    statement_template_.append(" ").append(preparedStatement.statement_template());
    prepared_statement_->AddAll(preparedStatement.values());
    if (prepared_statement_->columns().empty()) {
      prepared_statement_->AddColumn(preparedStatement.columns());
    }
    return This();
  }

  template <typename CLAUSE>
  auto &
  operator<<(CLAUSE clause) {
    return AddClause(clause);
  }

  virtual ~Statement();

 protected:
  std::string statement_template_;
  std::unique_ptr<PreparedStatement> prepared_statement_;
  StatementType type_{};

 private:
  std::string transaction_id_ = winter::random::uuid();
  Children &
  This() {
    return dynamic_cast<Children &>(*this);
  }
};

template <typename Children>
Statement<Children>::~Statement() = default;

}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_STATEMENT */
