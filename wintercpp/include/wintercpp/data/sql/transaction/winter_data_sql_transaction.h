//
// Created by Samuel Azcona on 15/03/2020.
//

#ifndef WINTER_DATA_SQL_TRANSACTION
#define WINTER_DATA_SQL_TRANSACTION

#include <wintercpp/data/sql/connection/winter_data_sql_connection.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>
#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement.h>

#include <deque>
#include <iostream>
#include <map>

#include "wintercpp/data/response/winter_data_response_status.h"

namespace winter::data::sql {

class ITransaction {
 public:
  virtual void Rollback() const = 0;
  virtual void Commit() const = 0;
  virtual TransactionIsolationType isolation() const = 0;
  virtual bool ignore_error() const = 0;
};

template <
    typename TTransactionImpl,
    typename TConnectionImpl,
    typename TConnectionType,
    typename TResponse>
class Transaction : public virtual ITransaction {
 public:
  explicit Transaction(
      std::shared_ptr<SQLConnection<TConnectionImpl, TConnectionType, TResponse> > connection,
      TransactionIsolationType isolation_type = TransactionIsolationType::DEFAULT,
      bool partial_commit = false);

  template <typename T>
  T Execute(const std::function<T(TTransactionImpl &)> &statements);

  TResponse Execute(IStatement &statement);

  TResponse Execute(const PreparedStatement &prepared_statement);

  /*   template <typename T>
  T operator()(const std::function<T(TTransactionImpl &)> &statements);

  TResponse operator()(const PreparedStatement &prepared_statement);

  TResponse operator()(IStatement &statement); */

  TransactionIsolationType isolation() const override;

  bool ignore_error() const override;

  void Commit() const override;

  void Rollback() const override;

  winter::data::ResponseStatus status() const;

  ~Transaction();

 private:
  std::shared_ptr<SQLConnection<TConnectionImpl, TConnectionType, TResponse> > connection_;
  TransactionIsolationType isolation_type_;
  bool partial_commit_;
  std::map<std::string, bool> operations_status_;
  TTransactionImpl &This();

  void status(const ResponseStatus &status);
};

}  // namespace winter::data::sql

#include "winter_data_sql_transaction.tpp"

#endif /* WINTER_DATA_SQL_TRANSACTION */
