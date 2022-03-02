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

namespace winter::data::sql_impl {

/**
 * Interface to create basic SQL connection this is used for example on winter::mysql, winter::postgres, winter::mariadb
 */
template <typename TConnectionImpl, typename TConnectionType, typename TResponse>
class SQLConnection : public winter::templates::
			  Connection<TConnectionImpl, TConnectionType> {
 public:
  SQLConnection(const SQLConnection &) = delete;
  SQLConnection &operator=(const SQLConnection &) = delete;

  /**
   * @brief simple function that execute the prepared statement query then this internally should encapsulate the logic to insert, update, select, remove, etc.
   * @see PreparedStatement
   * @param PreparedStatement
   * @return TResponse
   */
  virtual TResponse Execute(const PreparedStatement &query) = 0;

  /**
   * @brief basic function that implement how to initialize the transaction with his isolation level and start transaction
   * @param TransactionIsolationType
   * @return
   */
  virtual void PrepareTransaction(const TransactionIsolationType &isolation) = 0;

  /**
   * @brief Manuall commit the transaction
   * @return void
   */
  virtual void Commit() const = 0;

  /**
   * @brief manual rollback the transaction
   * @return void
   */
  virtual void Rollback() const = 0;

 protected:
  explicit SQLConnection(TConnectionType *conn) :
      winter::templates::Connection<TConnectionImpl, TConnectionType>(conn){};
};
}  // namespace winter::data::sql_impl

#endif /* WINTER_DATA_SQL_CONNECTION */
