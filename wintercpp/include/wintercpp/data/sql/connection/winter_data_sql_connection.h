//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-09-27.
//

#ifndef WINTER_DATA_SQL_CONNECTION
#define WINTER_DATA_SQL_CONNECTION

#include <wintercpp/data/sql/preparedstatement/winter_data_sql_prepared_statement.h>
#include <wintercpp/data/sql/statement/winter_data_sql_statement_type.h>
#include <wintercpp/data/sql/transaction/winter_data_sql_transaction_type.h>
#include <wintercpp/template/winter_connection_template.h>

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

namespace winter::data::sql {

template <typename TConnectionImpl, typename TConnectionType, typename TResponse>
class SQLConnection : public winter::templates::
			  Connection<TConnectionImpl, TConnectionType> {
 public:
  SQLConnection(const SQLConnection &) = delete;
  SQLConnection &operator=(const SQLConnection &) = delete;

  virtual TResponse Execute(const PreparedStatement &query) = 0;

  virtual void PrepareTransaction(const TransactionIsolationType &isolation) = 0;

  virtual void Commit() const = 0;

  virtual void Rollback() const = 0;

  protected:
    explicit SQLConnection(TConnectionType *conn) : winter::templates::Connection<TConnectionImpl, TConnectionType>(conn){};
};
}  // namespace winter::data::sql

#endif /* WINTER_DATA_SQL_CONNECTION */
