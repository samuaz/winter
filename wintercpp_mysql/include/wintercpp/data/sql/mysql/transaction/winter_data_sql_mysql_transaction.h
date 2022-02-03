//
// Created by samuaz on 6/9/21.
//

#ifndef WINTER_DATA_SQL_MYSQL_TRANSACTION
#define WINTER_DATA_SQL_MYSQL_TRANSACTION

#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>
#include <wintercpp/data/sql/response/winter_data_sql_response.h>
#include <wintercpp/data/sql/transaction/winter_data_sql_transaction.h>

namespace winter::data::sql_impl::mysql {

using namespace winter::data::sql_impl::mysql::connection;

class Transaction final : public virtual winter::data::sql_impl::Transaction<
			      Transaction,
			      Connection,
			      ::sql::Connection,
			      MysqlResponse> {
 public:
  Transaction(
      const std::shared_ptr<Connection> &conn,
      TransactionIsolationType isolation = TransactionIsolationType::DEFAULT,
      bool partial_commit = false) :
      winter::data::sql_impl::Transaction<Transaction, Connection, ::sql::Connection, MysqlResponse>(conn, isolation, partial_commit) {}
};

}  // namespace winter::data::sql_impl::mysql

typedef winter::data::sql_impl::mysql::Transaction MysqlTransaction;

#endif /* WINTER_DATA_SQL_MYSQL_TRANSACTION */