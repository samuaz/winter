//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mysql/transaction/winter_data_sql_mysql_transaction.h>
#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::sql_impl::mysql::mariadb_impl {

#define MARIADB_TRANSACTION_IMPL = winter::data::sql_impl::mysql : Transaction<winter::data::sql_impl::mysql::connection::mariadb_impl::Connection>

class Transaction : public virtual winter::data::sql_impl::mysql : Transaction<winter::data::sql_impl::mysql::connection::mariadb_impl::Connection> {
 public:
  explicit Transaction(
      const std::shared_ptr<Connection> &conn,
      TransactionIsolationType isolation = TransactionIsolationType::DEFAULT,
      bool partial_commit = false) :
      MARIADB_TRANSACTION_IMPL(conn, isolation, partial_commit) {
  }
};
}  // namespace winter::data::sql_impl::mysql::mariadb_impl

#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
