//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
#define WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H

/*#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mysql/transaction/winter_data_sql_mysql_transaction.h>
#include <wintercpp/winter_mysql.h>

#include <mariadb/conncpp.hpp>

namespace winter::data::sql_impl::mysql::mariadb_impl {

#define MARIADB_TRANSACTION_IMPL winter::data::sql_impl::mysql::Transaction<winter::data::sql_impl::mysql::connection::mariadb_impl::Connection, winter::data::sql_impl::mysql::mariadb_impl::Response>

class Transaction : public virtual MARIADB_TRANSACTION_IMPL {
 public:
  explicit Transaction(
      const std::shared_ptr<winter::data::sql_impl::mysql::connection::mariadb_impl::Connection> &conn,
      TransactionIsolationType isolation = TransactionIsolationType::DEFAULT,
      bool partial_commit = false) :
      MARIADB_TRANSACTION_IMPL(conn, isolation, partial_commit) {
  }
};
}*/
// namespace winter::data::sql_impl::mysql::mariadb_impl

#include <wintercpp/data/sql/mariadb/connection/winter_data_sql_mariadb_impl_connection.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>
#include <wintercpp/data/sql/response/winter_data_sql_response.h>
#include <wintercpp/data/sql/transaction/winter_data_sql_transaction.h>
#include <wintercpp/winter_mysql.h>

namespace winter::data::mariadb {

using namespace winter::data::sql_impl::mysql::connection;

class Transaction : public virtual winter::data::sql_impl::Transaction<
			winter::data::mariadb::Transaction,
			winter::data::mariadb::connection::Connection,
			winter::data::mariadb::Response> {
 public:
  Transaction(
      const shared_ptr<winter::data::mariadb::connection::Connection>& connection,
      TransactionIsolationType isolationType,
      bool partialCommit) :
      winter::data::sql_impl::Transaction<
	  winter::data::mariadb::Transaction,
	  winter::data::mariadb::connection::Connection,
	  winter::data::mariadb::Response>(connection, isolationType, partialCommit) {}
};

}  // namespace winter::data::mariadb

#endif	// WINTERCPP_WINTER_DATA_SQL_MARIADB_IMPL_TRANSACTION_H
