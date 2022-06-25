//
// Created by samuaz on 6/1/22.
//

#ifndef WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_TRANSACTION_H
#define WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_TRANSACTION_H

#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_impl_connection.h>
#include <wintercpp/data/sql/mysql/connection/winter_data_sql_mysql_connection.h>
#include <wintercpp/winter_mysql_core.h>

namespace winter::data::mysql {

using namespace winter::data::sql_impl::mysql::connection;

class Transaction : public virtual winter::data::sql_impl::Transaction<
			winter::data::mysql::Transaction,
			winter::data::mysql::connection::Connection,
			winter::data::mysql::Response> {
 public:
  Transaction(
      const shared_ptr<winter::data::mysql::connection::Connection>& connection,
      TransactionIsolationType isolationType,
      bool partialCommit) :
      winter::data::sql_impl::Transaction<
	  winter::data::mysql::Transaction,
	  winter::data::mysql::connection::Connection,
	  winter::data::mysql::Response>(connection, isolationType, partialCommit) {}
};

}  // namespace winter::data::mysql

#endif	// WINTERCPP_WINTER_DATA_SQL_MYSQL_IMPL_TRANSACTION_H
